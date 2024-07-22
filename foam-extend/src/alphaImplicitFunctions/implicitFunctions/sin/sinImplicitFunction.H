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
    Foam::implicitFunctions::sinImplicitFunction

Description

    Original code supplied by Henning Scheufler, DLR (2019)
    Modification Gabriel M. Magalhães, University of Minho (2024)

SourceFiles
    sinImplicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_sinImplicitFunction_H
#define implicitFunction_sinImplicitFunction_H

#include "implicitFunction.H"
#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunctions
{

/*---------------------------------------------------------------------------*\
                     Class sinImplicitFunction Declaration
\*---------------------------------------------------------------------------*/

class sinImplicitFunction
:
    public implicitFunction
{
private:

    // Private Data

        //- Origin point
        const scalar period_;

        //- Radius
        const scalar phase_;

        const scalar amplitude_;

        vector up_;

        vector direction_;

        const vector origin_;


public:

    //- Runtime type information
    TypeName("sin");


    // Constructors

        //- Construct from components
        sinImplicitFunction
        (
            const scalar period,
            const scalar phase,
            const scalar amplitude,
            const vector& direction,
            const vector& up,
            const vector& origin
        );

        //- Construct from dictionary (used by implicitFunctions)
        explicit sinImplicitFunction(const dictionary& dict);


    //- Destructor
    virtual ~sinImplicitFunction() = default;


    // Member Functions
        virtual scalar impl_func(const vector& p) const
        {
            const scalar x = (p - origin_) & direction_;
            const scalar z = (p - origin_) & -up_;

            return
              - z
              + amplitude_
               *Foam::sin(2*mathematicalConstant::pi*x/period_ + phase_);
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace implicitFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
