/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// #include <iostream>
// using namespace std;

UnlimitedInt *hcf(UnlimitedInt *n1, UnlimitedInt *n2)
{
    string s1 = n1->to_string();
    string s2 = n2->to_string();
    if (n1->get_sign() == -1 || n2->get_sign() == -1)
    {
        if (s1[0] == '-')
        {
            s1.erase(0, 1);
        }
        if (s2[0] == '-')
        {
            s2.erase(0, 1);
        }
    }
    UnlimitedInt *a = new UnlimitedInt(s1);
    UnlimitedInt *b = new UnlimitedInt(s2);
    UnlimitedInt *c = UnlimitedInt::sub(a, b);
    if (a->to_string() == "0")
    {
        return b;
    }
    else if (b->to_string() == "0")
    {
        return a;
    }
    else if (c->get_sign() == -1)
    {
        return hcf(b, a);
    }
    else
    {
        return hcf(b, a->mod(a, b));
    }
}

UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt(1);
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if(den->to_string()=="0"){
        p= new UnlimitedInt("0");
        q= new UnlimitedInt("0");
    }
    else{
        p = num;
        q = den;
        UnlimitedInt *cf = hcf(p, q);
        p = p->div(p, cf);
        q = q->div(q, cf);
    }
    if(p->get_sign()==1 && q->get_sign()==-1){
        UnlimitedInt* neg=new UnlimitedInt("-1");
        p=p->div(p,neg);
        q=q->div(q,neg);
        delete neg;
    }
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *r1, UnlimitedRational *r2)
{
    if(r1->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r1->get_p(),r1->get_q());
        return res;
    }
    else if(r2->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r2->get_p(),r2->get_q());
        return res;
    }
    UnlimitedInt *p1 = r1->get_p();
    UnlimitedInt *q1 = r1->get_q();
    UnlimitedInt *p2 = r2->get_p();
    UnlimitedInt *q2 = r2->get_q();
    UnlimitedInt *p1q2 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt *p2q1 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt *numerator = UnlimitedInt::add(p1q2, p2q1);
    UnlimitedInt *denominator = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* result=new UnlimitedRational(numerator, denominator);
    delete p1q2;
    delete p2q1;
    return result;
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *r1, UnlimitedRational *r2)
{
    if(r1->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r1->get_p(),r1->get_q());
        return res;
    }
    else if(r2->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r2->get_p(),r2->get_q());
        return res;
    }
    UnlimitedInt *p1 = r1->get_p();
    UnlimitedInt *q1 = r1->get_q();
    UnlimitedInt *p2 = r2->get_p();
    UnlimitedInt *q2 = r2->get_q();
    UnlimitedInt *p1q2 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt *p2q1 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt *numerator = UnlimitedInt::sub(p1q2, p2q1);
    UnlimitedInt *denominator = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* result=new UnlimitedRational(numerator, denominator);
    delete p1q2;
    delete p2q1;
    return result;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *r1, UnlimitedRational *r2)
{
    if(r1->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r1->get_p(),r1->get_q());
        return res;
    }
    else if(r2->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r2->get_p(),r2->get_q());
        return res;
    }
    UnlimitedInt *numerator = UnlimitedInt::mul(r1->get_p(), r2->get_p());
    UnlimitedInt *denominator = UnlimitedInt::mul(r1->get_q(), r2->get_q());
    return new UnlimitedRational(numerator, denominator);
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *r1, UnlimitedRational *r2)
{
    if(r1->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r1->get_p(),r1->get_q());
        return res;
    }
    else if(r2->get_frac_str()=="0/0"){
        UnlimitedRational* res= new UnlimitedRational(r2->get_p(),r2->get_q());
        return res;
    }
    UnlimitedInt *numerator = UnlimitedInt::mul(r1->get_p(), r2->get_q());
    UnlimitedInt *denominator = UnlimitedInt::mul(r1->get_q(), r2->get_p());
    return new UnlimitedRational(numerator, denominator);
}

// int main()
// {
//     UnlimitedInt *a = new UnlimitedInt("1");
//     UnlimitedInt *b = new UnlimitedInt("1");
//     UnlimitedRational *c = new UnlimitedRational(a, b);
//     UnlimitedRational *d = new UnlimitedRational(b, a);
//     UnlimitedRational *ad = UnlimitedRational::add(c, d);
//     UnlimitedRational *bd = UnlimitedRational::sub(c, d);
//     UnlimitedRational *cd = UnlimitedRational::mul(c, d);
//     UnlimitedRational *dd = UnlimitedRational::div(c, d);
//     cout << ad->get_frac_str() << endl;
//     cout << bd->get_frac_str() << endl;
//     cout << cd->get_frac_str() << endl;
//     cout << dd->get_frac_str() << endl;
//     return 0;
// }