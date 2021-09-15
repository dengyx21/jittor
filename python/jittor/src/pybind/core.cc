// ***************************************************************
// Copyright (c) 2021 Jittor. All Rights Reserved. 
// Maintainers: Dun Liang <randonlang@gmail.com>. 
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.
// ***************************************************************
#include "core.h"
#include "grad.h"
#include "pyjt/py_obj_holder.h"
#include "init.h"

namespace jittor {

// Those function is generated by python
EXTERN_LIB void pyjt_def_all(PyObject* m);

vector<VarHolder*> _grad(VarHolder* loss, const vector<VarHolder*>& targets) {
   vector<Var*> vs;
   vs.reserve(targets.size());
   for (auto* v : targets) vs.push_back(v->var);
   auto grads = grad(loss->var, vs);
   vector<VarHolder*> grads_hold;
   grads_hold.reserve(targets.size());
   for (auto& grad : grads)
       grads_hold.push_back(new VarHolder(move(grad)));
   return grads_hold;
}

} // jittor

static void init_module(PyModuleDef* mdef, PyObject* m) {
    mdef->m_doc = "Inner c++ core of jittor";
    jittor::init();
    jittor::pyjt_def_all(m);
}
PYJT_MODULE_INIT(jittor_core);