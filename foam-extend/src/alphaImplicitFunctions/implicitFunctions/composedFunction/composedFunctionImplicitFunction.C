/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     5.0
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

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
                << "Supported actions are: " << nl
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

    // convert dictionary to map
    wordList toc = funcDict.toc();

    label funci = 0;

    forAll(toc, i)
    {
        word keyword = toc[i];
        if (!funcDict.isDict(keyword))
        {
            FatalIOErrorInFunction(funcDict)
                << "Entry " << keyword << " is not a dictionary" << endl
                << exit(FatalIOError);
        }

        const dictionary & subdict = funcDict.subDict(keyword);

        functions_.set
        (
            funci,
            implicitFunction::New(subdict.lookup("type"), subdict)
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
