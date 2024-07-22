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
    Foam::implicitFunctions::sphereImplicitFunction

Description
    Creates a sphere

    Original code supplied by Henning Scheufler, DLR (2019)
    Modification Gabriel M. Magalhães, University of Minho (2024)

SourceFiles
    sphereImplicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_sphereImplicitFunction_H
#define implicitFunction_sphereImplicitFunction_H

#include "implicitFunction.H"
#include "point.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunctions
{

/*---------------------------------------------------------------------------*\
                   Class sphereImplicitFunction Declaration
\*---------------------------------------------------------------------------*/

class sphereImplicitFunction
:
    public implicitFunction
{
    // Private Data

        //- Origin point
        const point origin_;

        //- Radius
        const scalar radius_;

        const scalar scale_;


public:

    //- Runtime type information
    TypeName("sphere");


    // Constructors

        //- Construct from components
        sphereImplicitFunction
        (
            const point&,
            const scalar radius,
            const scalar scale
        );

        //- Construct from dictionary
        explicit sphereImplicitFunction(const dictionary& dict);


    //- Destructor
    virtual ~sphereImplicitFunction() = default;


    // Member Functions
        virtual scalar impl_func(const vector& p) const
        {
            return (sqr(mag(p - origin_)) - sqr(radius_))*scale_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace implicitFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
