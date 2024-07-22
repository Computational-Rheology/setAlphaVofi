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

Application
    setAlphaVofi

Description
    Uses Vofi 2.0 (http://doi.org/10.1016/j.cpc.2022.108506) external library
    to create a volume fraction field from the implicit functions.

    Original code supplied by Gabriel M. Magalhães, University of Minho (2024)

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "implicitFunction.H"

#include <vofi.h>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

autoPtr<implicitFunction> implicitFunc;

vofi_real impl_func(vofi_creal xyz[], void * const param)
{
    vector p;
    for (label i=0 ; i < 3 ; i++)
    {
        p[i] =  xyz[i];
    }

    return implicitFunc->impl_func(p);
}

void setAlpha
(
    volScalarField& alpha1,
    dictionary& setAlphaVofiDict
)
{
    implicitFunc = implicitFunction::New
    (
        setAlphaVofiDict.lookup("type"),
        setAlphaVofiDict
    );

    const fvMesh& mesh = alpha1.mesh();

    const volVectorField& centres = mesh.C();
    const surfaceVectorField& Cf = mesh.Cf();
    
    label ndim0=3;
    scalar param[4],xex[4];
    scalar xloc[3], h0[3];
    // 1D array of two integers, to print (=1) or not to print (=0)
    // the heights and the triangulation data from Vofi
    label nvis[2] = {0,0};

    // 1D array of 2 integers, to compute (=1) or not to compute (=0),
    //     the centroid coordinates and the interface length/area;
    label nex[2] = {0,0};

    // 1D array of four integers, with the minimum and maximum number
    // of nodes allowed by the user, for both the internal (npts[0]
    // and npts[1]) and the external (npts[2] and npts[3]) integrations;
    // to be effective each integer npts should be in the range:
    // 3 <= npts <= 20
    label npts[4] = {4,4,4,4};
    const word validShape = "hex";
    const cellShapeList& cellShapes = mesh.cellShapes();

    forAll(alpha1, cellI)
    {
        if (cellShapes[cellI].model().name() == validShape)
        {
            const edgeList& cellEdges = cellShapes[cellI].edges();
            scalarList dEdgesZ(cellEdges.size());
            scalarList dEdgesY(cellEdges.size());
            scalarList dEdgesX(cellEdges.size());
            forAll(cellEdges, edgei)
            {
                dEdgesZ[edgei] = mag(cellEdges[edgei].vec(mesh.points()).z());
                dEdgesY[edgei] = mag(cellEdges[edgei].vec(mesh.points()).y());
                dEdgesX[edgei] = mag(cellEdges[edgei].vec(mesh.points()).x());
            }
            h0[0] = max(dEdgesX);
            h0[1] = max(dEdgesY);
            h0[2] = max(dEdgesZ);

            for(label i=0; i < 3 ; i++)
            {
                xloc[i] = centres[cellI][i] - 0.5*h0[i];
            }      

            alpha1[cellI] = vofi_get_cc(impl_func, static_cast<double *> ( param),xloc,h0,
                    xex,nex,npts,nvis,ndim0);
        }
    }

    // Setting boundary alpha1 values (Not implemented)
    forAll(mesh.boundary(), patchi)
    {
        if (mesh.boundary()[patchi].size() > 0)
        {
            const label start = mesh.boundary()[patchi].patch().start();
            scalarField& alphap = alpha1.boundaryField()[patchi];

            forAll(alphap, patchFacei)
            {
                const label facei = patchFacei + start;

                for(label i=0; i < 3 ; i++)
                {
                    xloc[i] = Cf[facei][i] - 0.5*h0[i];
                } 
                alphap[patchFacei] = vofi_get_cc(impl_func, static_cast<double *> ( param),xloc,h0,
				  xex,nex,npts,nvis,ndim0);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Uses Vofi external lib to initialize the volume fraction field from an "
        "implicit function."
    );

    argList::addOption
    (
        "dict",
        "file",
        "Alternative setAlphaVofiDict dictionary"
    );
    #include "addRegionOption.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createNamedMesh.H"

    const word dictName("setAlphaVofiDict");
    #include "setSystemMeshDictionaryIO.H"

    IOdictionary setAlphaVofiDict(dictIO);

    Info<< "Reading " << setAlphaVofiDict.name() << endl;

    const word fieldName = setAlphaVofiDict.lookup("field");
    const bool invert = setAlphaVofiDict.lookupOrDefault("invert", false);

    Info<< "Reading field " << fieldName << nl << endl;
    volScalarField alpha1
    (
        IOobject
        (
            fieldName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    setAlpha(alpha1,setAlphaVofiDict);

    ISstream::defaultPrecision(18);

    if (invert)
    {
        alpha1 = scalar(1) - alpha1;
    }

    Info<< "Writing new alpha field " << alpha1.name() << endl;
    alpha1.write();

    const scalarField& alpha = alpha1.internalField();

    Info<< "sum(alpha*V):" << gSum(mesh.V()*alpha)
        << ", 1-max(alpha1): " << 1 - gMax(alpha)
        << " min(alpha1): " << gMin(alpha) << endl;

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
