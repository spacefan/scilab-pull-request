// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Antoine ELIAS
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//

// <-- JVM NOT MANDATORY -->

function v = while_return()
    v = 0;
    while v == 0
        v = 1;
        return
        v = 2;
    end
endfunction

function v = while_if_return()
    v = 0;
    flag = 0;
    while v == 0
        if v == 0 then
            v = 1;
            return
            v = 2;
        end
    end
    v = 3;
endfunction

function v = for_return()
    v = 0;
    for i = 1:1
        v = 1;
        return
        v = 2;
    end
endfunction

function v = for_if_return()
    v = 0;
    flag = 0;
    for i = 1:1
        if v == 0 then
            v = 1;
            return
            v = 2;
        end
    end
    v = 3;
endfunction

assert_checkequal(while_return(), 1);
assert_checkequal(while_if_return(), 1);
assert_checkequal(for_return(), 1);
assert_checkequal(for_if_return(), 1);