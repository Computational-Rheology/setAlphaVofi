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

Class
    Foam::implicitFunctions::ellipsoidImplicitFunction

Description
    creates an ellipsoidImplicitFunction

    Original code supplied by Henning Scheufler, DLR (2019)
    Modification Gabriel M. Magalhães, University of Minho (2024)

SourceFiles
    ellipsoidImplicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_ellipsoidImplicitFunction_H
#define implicitFunction_ellipsoidImplicitFunction_H

#include "implicitFunction.H"
#include "mathematicalConstants.H"
#include "point.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunctions
{

/*---------------------------------------------------------------------------*\
                  Class ellipsoidImplicitFunction Declaration
\*---------------------------------------------------------------------------*/

class ellipsoidImplicitFunction
:
    public implicitFunction
{
    // Private Member Data

        //- Origin point
        const point origin_;

        //- Axis
        const vector semiAxis_;


public:

    //- Runtime type information
    TypeName("ellipsoid");


    // Constructors

        //- Construct from components
        ellipsoidImplicitFunction(const point& origin, const vector& semiAxis);

        //- Construct from dictionary
        explicit ellipsoidImplicitFunction(const dictionary& dict);


    //- Destructor
    virtual ~ellipsoidImplicitFunction() = default;


    // Member Functions
    virtual scalar impl_func(const vector& p) const
    {
        return
            (
                sqr((p.x() - origin_.x())/semiAxis_.x())
              + sqr((p.y() - origin_.y())/semiAxis_.y())
              + sqr((p.z() - origin_.z())/semiAxis_.z())
            ) - 1;
    }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace implicitFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
