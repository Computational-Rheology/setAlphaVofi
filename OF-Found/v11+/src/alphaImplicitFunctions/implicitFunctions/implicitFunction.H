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
    Foam::implicitFunction

Description
    Base class for implicit functions

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    implicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_H
#define implicitFunction_H

#include "vector.H"
#include "dictionary.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class implicitFunction Declaration
\*---------------------------------------------------------------------------*/

class implicitFunction
{
public:

    //- Runtime type information
    TypeName("implicitFunction");

    //- Declare run-time constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        implicitFunction,
        dictionary,
        (
            const dictionary& dict
        ),
        (dict)
    );


    // Constructors

        //- Default construct
        implicitFunction() = default;


        //- Return a reference to the selected implicitFunction
        static autoPtr<implicitFunction> New
        (
            const word& implicitFunctionType,
            const dictionary& dict
        );


    //- Destructor
    virtual ~implicitFunction() = default;


    // Member Functions
        virtual scalar impl_func(const vector& p) const
        {
            return GREAT;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
