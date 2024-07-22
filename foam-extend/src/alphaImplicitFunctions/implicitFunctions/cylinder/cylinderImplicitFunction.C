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

#include "cylinderImplicitFunction.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace implicitFunctions
    {
        defineTypeNameAndDebug(cylinderImplicitFunction, 0);
        addToRunTimeSelectionTable
        (
            implicitFunction,
            cylinderImplicitFunction,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::implicitFunctions::cylinderImplicitFunction::cylinderImplicitFunction
(
    const point& origin,
    const scalar radius,
    const scalar scale,
    const vector& direction
)
:
    origin_(origin),
    radius_(radius),
    scale_(scale),
    direction_(direction),
    project_(tensor::I - direction_*direction_) // outer product
{
    direction_ /= (mag(direction_) + SMALL);
}


Foam::implicitFunctions::cylinderImplicitFunction::cylinderImplicitFunction
(
    const dictionary& dict
)
:
    // __INTEL_COMPILER bug with inheriting constructors?? (issue #1821)
    origin_(dict.lookup("origin")),
    radius_(readScalar(dict.lookup("radius"))),
    scale_(dict.lookupOrDefault<scalar>("scale", 1)),
    direction_(dict.lookup("direction")),
    project_(tensor::I - direction_*direction_) // outer product
{
    direction_ /= mag(direction_) + SMALL;
}


// ************************************************************************* //
