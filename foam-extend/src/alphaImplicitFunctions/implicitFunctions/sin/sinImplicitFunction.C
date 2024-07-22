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

#include "sinImplicitFunction.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace implicitFunctions
    {
        defineTypeNameAndDebug(sinImplicitFunction, 0);
        addToRunTimeSelectionTable
        (
            implicitFunction,
            sinImplicitFunction,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::implicitFunctions::sinImplicitFunction::sinImplicitFunction
(
    const scalar period,
    const scalar phase,
    const scalar amplitude,
    const vector& direction,
    const vector& up,
    const vector& origin
)
:
    period_(period),
    phase_(phase),
    amplitude_(amplitude),
    up_(up), 
    direction_(direction), 
    origin_(origin)
{
    direction_ /= mag(direction_)  + SMALL;
    up_ /= mag(up_)  + SMALL;
}


Foam::implicitFunctions::sinImplicitFunction::sinImplicitFunction
(
    const dictionary& dict
)
:
    // __INTEL_COMPILER bug with inheriting constructors?? (issue #1821)
    period_(readScalar(dict.lookup("period"))),
    phase_(dict.lookupOrDefault("phase", 0)),
    amplitude_(readScalar(dict.lookup("amplitude"))),
    up_(dict.lookup("up")),
    direction_(dict.lookup("direction")),
    origin_(dict.lookup("origin"))
{
    direction_ /= mag(direction_) + SMALL;
    up_ /= mag(up_) + SMALL;
}


// ************************************************************************* //
