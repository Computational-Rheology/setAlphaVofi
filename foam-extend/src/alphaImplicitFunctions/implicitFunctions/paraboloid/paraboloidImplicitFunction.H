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
    Foam::implicitFunctions::paraboloidImplicitFunction

Description
    creates a paraboloid

    Original code supplied by Henning Scheufler, DLR (2019)
    Modification Gabriel M. Magalhães, University of Minho (2024)

SourceFiles
    paraboloidImplicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_paraboloidImplicitFunction_H
#define implicitFunction_paraboloidImplicitFunction_H

#include "implicitFunction.H"
#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunctions
{

/*---------------------------------------------------------------------------*\
                 Class paraboloidImplicitFunction Declaration
\*---------------------------------------------------------------------------*/

class paraboloidImplicitFunction
:
    public implicitFunction
{
    // Private Data

        //- Coefficients of ax^2 + bx*y + cy^2
        const vector coeffs_;


public:

    //- Runtime type information
    TypeName("paraboloid");


    // Constructors

        //- Construct from components
        explicit paraboloidImplicitFunction(const vector& coeffs);

        //- Construct from dictionary
        explicit paraboloidImplicitFunction(const dictionary& dict);


    //- Destructor
    virtual ~paraboloidImplicitFunction() = default;


    // Member Functions
        virtual scalar impl_func(const vector& p) const
        {
            return
              - coeffs_.x()*sqr(p.x())
              - coeffs_.y()*p.x()*p.y()
              - coeffs_.z()*sqr(p.y())
              + p.z();
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace implicitFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
