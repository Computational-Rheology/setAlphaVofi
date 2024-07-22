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
    Foam::implicitFunction

Description
    Base class for implicit functions

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    implicitFunction.C

\*---------------------------------------------------------------------------*/

#ifndef implicitFunction_H
#define implicitFunction_H

#include "autoPtr.H"
#include "dictionary.H"
#include "vector.H"
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
