/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2010-2010 - DIGITEO - Bernard HUGUENEY
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#include <iostream>
#include "sparse_gw.hxx"
#include "function.hxx"
#include "sparse.hxx"

extern "C"
{
#include "charEncoding.h"
#include "Scierror.h"
#include "localization.h"
}

extern "C" int C2F(ordmmd)(int* neqns, int* xadj, int* adjncy, int* invp, int* perm,
                           int* iwsiz, int* iwork, int* nofsub, int* iflag);

using namespace types;

Function::ReturnValue sci_ordmmd(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 3)
    {
        Scierror(999, _("%s: Wrong number of input argument(s): %d expected.\n"), "ordmmd", 3);
        return Function::Error;
    }

    if (_iRetCount != 3)
    {
        Scierror(999, _("%s: Wrong number of output arguments: %d expected.\n"), "ordmmd", 3);
        return Function::Error;
    }


    //get argument #1
    if (in[0]->isDouble() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A matrix of integer value expected.\n"), "ordmmd", 1);
        return Function::Error;
    }

    Double* pdbl1 = in[0]->getAs<Double>();
    pdbl1->convertToInteger();
    int* pXADJ = (int*)pdbl1->get();

    //get argument #2
    if (in[1]->isDouble() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A matrix of integer value expected.\n"), "ordmmd", 2);
        return Function::Error;
    }

    Double* pdbl2 = in[1]->getAs<Double>();
    pdbl2->convertToInteger();
    int* pADJNCY = (int*)pdbl2->get();

    //get argument #3
    Double* pdbl3 = in[2]->getAs<Double>();
    if (in[2]->isDouble() == false || pdbl3->getSize() != 1)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: An integer value expected.\n"), "ordmmd", 3);
        return Function::Error;
    }

    int NEQNS = (int)pdbl3->get(0);

    Double* pdbl4 = new Double(NEQNS, 1);
    pdbl4->convertToInteger();

    Double* pdbl5 = new Double(NEQNS, 1);
    pdbl5->convertToInteger();

    Double* pdbl6 = new Double(1, 1);
    pdbl6->convertToInteger();

    Double* pdbl7 = new Double(4 * NEQNS, 1);
    pdbl7->convertToInteger();
    int iSize = 4 * NEQNS;

    int iFlag = 0;
    C2F(ordmmd)(&NEQNS, (int*)pdbl1->get(), (int*)pdbl2->get(), (int*)pdbl5->get(),
                (int*)pdbl4->get(), &iSize, (int*)pdbl7->get(), (int*)pdbl6->get(), &iFlag);

    if (iFlag)
    {
        Scierror(999, _("%s: insufficient working storage"), "ordmmd");
        return Function::Error;
    }

    pdbl1->convertFromInteger();
    pdbl2->convertFromInteger();
    pdbl4->convertFromInteger();
    pdbl5->convertFromInteger();
    pdbl6->convertFromInteger();
    pdbl7->convertFromInteger();
    delete pdbl7;

    out.push_back(pdbl4);
    out.push_back(pdbl5);
    out.push_back(pdbl6);

    return Function::OK;
}
