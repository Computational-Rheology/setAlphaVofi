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

Class
    Foam::implicitFunctions::composedFunctionImplicitFunction

Description
    Handles multiple implicit functions and offers multiple ways to combine
    them

Usage
    Example of function object partial specification:
    \verbatim
    function composedFunctionImplicitFunction;
    action minDist;
    // following action are available:
    // "add" "subtract" "minDist" "intersect"
    composedFunctionImplicitFunctions
    {
        plane
        {
            function plane;
            origin (0 1. 0);
            normal (0 1 0);
        }

        sphere
        {
            function sphere;
            radius 0.4;
            origin (0.5 1.5 0.5);
            scale 1;
        }

        sphere2
        {
            function sphere;
            radius 0.4;
            origin (0.5 0.5 0.5);
            scale -1;
        }
    }
    \endverbatim

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    composedFunctionImplicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunctions_composedFunctionImplicitFunction_H
#define implicitFunctions_composedFunctionImplicitFunction_H

#include "implicitFunction.H"
#include "scalarField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunctions
{

/*---------------------------------------------------------------------------*\
              Class composedFunctionImplicitFunction Declaration
\*---------------------------------------------------------------------------*/

class composedFunctionImplicitFunction
:
    public implicitFunction
{
    public:
    // Public Member Data

        //- Enumeration defining the valid actions
        enum actionType
        {
            ADD,
            SUBTRACT,
            MINDIST,
            INTERSECT
        };

        //- The setActions text representations
        static const NamedEnum<actionType,4> actionTypeNames_;

    protected:
    // Private Member Data

        //- Stores the functions
        PtrList<implicitFunction> functions_;

        //- Action
        actionType action_;

        //- Needed for finding the closest function.
        //  Note: avoid creation every call
        mutable scalarField values_;

    // Private Member Functions

        label selectFunction(const scalarField& values) const;

        //- No copy construct
        composedFunctionImplicitFunction
        (
            const composedFunctionImplicitFunction&
        ) = delete;

        //- No copy assignment
        void operator=(const composedFunctionImplicitFunction&) = delete;


public:

    //- Runtime type information
    TypeName("composedFunction");


    // Constructors

        //- Construct from dictionary
        explicit composedFunctionImplicitFunction(const dictionary& dict);


    //- Destructor
    virtual ~composedFunctionImplicitFunction() = default;


    // Member Functions
        virtual scalar impl_func(const vector& p) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
} // End namespace implicitFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
