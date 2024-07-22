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

#include "sphereImplicitFunction.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace implicitFunctions
    {
        defineTypeNameAndDebug(sphereImplicitFunction, 0);
        addToRunTimeSelectionTable
        (
            implicitFunction,
            sphereImplicitFunction,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::implicitFunctions::sphereImplicitFunction::sphereImplicitFunction
(
    const point& origin,
    const scalar radius,
    const scalar scale
)
:
    origin_(origin),
    radius_(radius),
    scale_(scale)
{}


Foam::implicitFunctions::sphereImplicitFunction::sphereImplicitFunction
(
    const dictionary& dict
)
:
    sphereImplicitFunction
    (
        dict.lookup("origin"),
        readScalar(dict.lookup("radius")),
        dict.lookupOrDefault<scalar>("scale", 1)
    )
{}


// ************************************************************************* //
