/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "composedFunctionImplicitFunction.H"
#include "scalarField.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace implicitFunctions
    {
        defineTypeNameAndDebug(composedFunctionImplicitFunction, 0);
        addToRunTimeSelectionTable
        (
            implicitFunction,
            composedFunctionImplicitFunction,
            dictionary
        );
    }
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<>
const char*
Foam::NamedEnum
<
    Foam::implicitFunctions::composedFunctionImplicitFunction::actionType,
    4
>::names[] =
{
    "add",
    "subtract",
    "minDist",
    "intersect"
};

const Foam::NamedEnum
<
    Foam::implicitFunctions::composedFunctionImplicitFunction::actionType,
    4
> Foam::implicitFunctions::composedFunctionImplicitFunction::actionTypeNames_;

Foam::label
Foam::implicitFunctions::composedFunctionImplicitFunction::selectFunction
(
    const scalarField& values
) const
{
    switch (action_)
    {
        case actionType::MINDIST:
        {
            scalarField absVal(mag(values));
            return findMin(absVal);
        }
        case actionType::ADD:
        {
            return findMax(values);
        }
        case actionType::SUBTRACT:
        {
            // Note: start at the second entry
            const label idx = findMin(values, 1);

            if (values[idx] < values[0] && pos(values[0]))
            {
                return idx;
            }
            else
            {
                return 0;
            }
        }
        case actionType::INTERSECT:
        {
            return findMin(values);
        }
        default:
        {
            FatalErrorInFunction
                << "This action is not supported  only " << nl
                << "Supported modes are: " << nl
                << actionTypeNames_
                << abort(FatalError);
        }
    }

    return -1;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::implicitFunctions::composedFunctionImplicitFunction::
composedFunctionImplicitFunction
(
    const dictionary& dict
)
:
    functions_(),
    action_(actionTypeNames_.read(dict.lookup("action"))),
    values_()
{
    const dictionary& funcDict = dict.subDict("composedFunction");

    functions_.resize(funcDict.size());
    values_.resize(funcDict.size(), Zero);

    label funci = 0;

    for (const entry& dEntry : funcDict)
    {
        const word& key = dEntry.keyword();

        if (!dEntry.isDict())
        {
            FatalIOErrorInFunction(funcDict)
                << "Entry " << key << " is not a dictionary" << endl
                << exit(FatalIOError);
        }

        const dictionary& subdict = dEntry.dict();

        functions_.set
        (
            funci,
            implicitFunction::New(subdict.lookup<word>("type"), subdict)
        );

        ++funci;
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
Foam::scalar Foam::implicitFunctions::composedFunctionImplicitFunction::impl_func
(
    const vector& p
) const
{
    forAll(values_,i)
    {
        values_[i] = functions_[i].impl_func(p);
    }

    const label idx = selectFunction(values_);

    return values_[idx];
}

// ************************************************************************* //
