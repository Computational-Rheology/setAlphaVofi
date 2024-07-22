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

#include "implicitFunction.H"
#include "error.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(implicitFunction, 0);
    defineRunTimeSelectionTable(implicitFunction, dictionary);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::implicitFunction> Foam::implicitFunction::New
(
    const word& implicitFunctionType,
    const dictionary& dict
)
{
    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(implicitFunctionType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalError
            << "implicitFunctionType::New(const dictionary&) : " << endl
            << "    unknown implicitFunctionType type "
            << implicitFunctionType
            << ", constructor not in hash table" << endl << endl
            << "    Valid implicitFunctionType types are :" << endl;
        Info<< dictionaryConstructorTablePtr_->sortedToc()
            << abort(FatalError);
    }

    return autoPtr<implicitFunction>(cstrIter()(dict));
}

// ************************************************************************* //
