/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "ulimitedint.h"
#include <iostream>
using namespace std;

bool abs_greater_than(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return true;
    }
    else if (i2->get_size() > i1->get_size())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < i1->get_size(); i++)
        {
            if (i1->get_array()[i] > i2->get_array()[i])
            {
                return true;
            }
            else if (i2->get_array()[i] > i1->get_array()[i])
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        return false;
    }
}

UnlimitedInt::UnlimitedInt()
{
    size = 0;
    sign = 1;
    capacity = 1000;
    unlimited_int = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        unlimited_int[i] = 0;
    }
}

UnlimitedInt::UnlimitedInt(string s)
{
    size = s.length();
    capacity = 1000000;
    unlimited_int = new int[capacity];

    if (s[0] == '-')
    {
        sign = -1;
        size--;
        s = s.substr(1);
    }
    else
    {
        sign = 1;
    }

    for (int i = 0; i < size; i++)
    {
        unlimited_int[i] = s[i] - '0';
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    string s = std::to_string(i);
    size = s.length();
    capacity = max(size, 1000);
    unlimited_int = new int[capacity];

    if (s[0] == '-')
    {
        sign = -1;
        size--;
        s = s.substr(1);
    }
    else
    {
        sign = 1;
    }

    for (int i = 0; i < size; i++)
    {
        unlimited_int[i] = s[i] - '0';
    }
}

UnlimitedInt::UnlimitedInt(int *unlimited_int, int cap, int sgn, int sz)
{
    capacity = cap;
    unlimited_int = new int[capacity];
    sign = sgn;
    size = sz;
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0")
    {
        UnlimitedInt *finalm = new UnlimitedInt(i2->to_string());
        return finalm;
    }
    else if (i2->to_string() == "0")
    {
        UnlimitedInt *finalm = new UnlimitedInt(i1->to_string());
        return finalm;
    }

    string final;
    int maxSize = max(i1->get_size(), i2->get_size());
    int carry = 0;
    int s = 1;

    if (i1->get_sign() == -1 && i2->get_sign() == -1)
    {
        s = -1;
    }
    else if ((i1->get_sign() == -1 && i2->get_sign() == 1) || (i2->get_sign() == -1 && i1->get_sign() == 1))
    {
        if (abs_greater_than(i1, i2))
        {
            s = i1->get_sign();
        }
        else if (abs_greater_than(i2, i1))
        {
            s = i2->get_sign();
        }
        else
        {
            return new UnlimitedInt(0);
        }
    }
    else
    {
        if (abs_greater_than(i2, i1))
        {
            s = i2->get_sign();
        }
    }

    if ((i1->get_sign() == 1 && i2->get_sign() == 1) || (i1->get_sign() == -1 && i2->get_sign() == -1))
    {
        for (int i = 0; i < maxSize; i++)
        {
            int sum = carry;
            if (i < i1->get_size())
            {
                sum += i1->get_array()[i1->get_size() - i - 1];
            }
            if (i < i2->get_size())
            {
                sum += i2->get_array()[i2->get_size() - i - 1];
            }
            final = std::to_string(sum % 10) + final;
            carry = sum / 10;
        }

        if (carry > 0)
        {
            final = std::to_string(carry) + final;
        }
        UnlimitedInt *res = new UnlimitedInt(final);
        res->sign = s;
        return res;
    }

    else if (i1->get_sign() == 1 && i2->get_sign() == -1)
    {
        for (int i = 0; i < maxSize; i++)
        {
            int sum = carry;
            if (abs_greater_than(i1, i2))
            {
                if (i < i1->get_size())
                {
                    sum += i1->get_array()[i1->get_size() - i - 1];
                }
                if (i < i2->get_size())
                {
                    sum -= i2->get_array()[i2->get_size() - i - 1];
                }
                if (sum < 0)
                {
                    sum = sum + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                final = std::to_string(sum % 10) + final;
                s = 1;
            }
            else if (abs_greater_than(i2, i1))
            {
                if (i < i1->get_size())
                {
                    sum -= i1->get_array()[i1->get_size() - i - 1];
                }
                if (i < i2->get_size())
                {
                    sum += i2->get_array()[i2->get_size() - i - 1];
                }
                if (sum < 0)
                {
                    sum = sum + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                final = std::to_string(sum % 10) + final;
                s = -1;
            }
        }
        if (carry > 0)
        {
            final = std::to_string(carry) + final;
        }
        int i = 0;
        int a = final.size();
        while (i < a)
        {
            if (final[i] == '0')
            {
                i++;
            }
            else
            {
                final = final.substr(i, final.size());
                break;
            }
        }
        UnlimitedInt *res = new UnlimitedInt(final);
        res->sign = s;
        return res;
    }

    else
    {
        for (int i = 0; i < maxSize; i++)
        {
            int sum = carry;
            if (abs_greater_than(i1, i2))
            {
                if (i <= i1->get_size())
                {
                    sum += i1->get_array()[i1->get_size() - i - 1];
                }
                if (i <= i2->get_size())
                {
                    sum -= i2->get_array()[i2->get_size() - i - 1];
                }
                if (sum < 0)
                {
                    sum = sum + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                final = std::to_string(sum % 10) + final;
                s = -1;
            }
            else if (abs_greater_than(i2, i1))
            {
                if (i <= i1->get_size())
                {
                    sum -= i1->get_array()[i1->get_size() - i - 1];
                }
                if (i <= i2->get_size())
                {
                    sum += i2->get_array()[i2->get_size() - i - 1];
                }
                if (sum < 0)
                {
                    sum = sum + 10;
                    carry = -1;
                }
                else
                {
                    carry = 0;
                }
                final = std::to_string(sum % 10) + final;
                s = 1;
            }
        }
        if (carry > 0)
        {
            final = std::to_string(carry) + final;
        }
        int i = 0;
        int a = final.size();
        while (i < a)
        {
            if (final[i] == '0')
            {
                i++;
            }
            else
            {
                final = final.substr(i, final.size());
                break;
            }
        }
        UnlimitedInt *res = new UnlimitedInt(final);
        res->sign = s;
        return res;
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *a = new UnlimitedInt(i1->to_string());
    UnlimitedInt *b = new UnlimitedInt(i2->to_string());
    if (i2->sign == 1)
    {
        b->sign = -1;
    }
    else
    {
        b->sign = 1;
    }
    UnlimitedInt *final = UnlimitedInt::add(a, b);
    delete a;
    delete b;
    return final;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int s = 1;
    if ((i1->sign == 1 && i2->sign == 1) || (i2->sign == -1 && i1->sign == -1))
    {
        s = 1;
    }
    else
    {
        s = -1;
    }
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *final = new UnlimitedInt("0");
        return final;
    }
    else
    {
        UnlimitedInt *a = new UnlimitedInt(i1->to_string());
        UnlimitedInt *b = new UnlimitedInt(i2->to_string());
        a->sign = 1;
        b->sign = 1;
        UnlimitedInt *e = new UnlimitedInt("0");
        if (abs_greater_than(i1, i2))
        {
            int i = 0;
            int maxS = b->size;
            while (i < maxS)
            {
                string finalekabaap = b->to_string();
                int m = int(finalekabaap[maxS - i - 1] - '0');
                UnlimitedInt *d = new UnlimitedInt("0");
                while (m > 0)
                {
                    d = add(d, a);
                    m--;
                }
                string finale;
                finale = d->to_string();
                delete d;
                int j = 0;
                while (j < i)
                {
                    finale = finale + "0";
                    j++;
                }
                UnlimitedInt *f = new UnlimitedInt(finale);
                e = add(e, f);
                i++;
            }
        }
        else
        {
            int i = 0;
            int maxS = a->size;
            while (i < maxS)
            {
                string finalekabaap = a->to_string();
                int m = int(finalekabaap[maxS - i - 1] - '0');
                UnlimitedInt *d = new UnlimitedInt("0");
                while (m > 0)
                {
                    d = add(d, b);
                    m--;
                }
                string finale;
                finale = d->to_string();
                delete d;
                int j = 0;
                while (j < i)
                {
                    finale = finale + "0";
                    j++;
                }
                UnlimitedInt *f = new UnlimitedInt(finale);
                e = add(e, f);
                i++;
            }
        }
        string finalfinal = e->to_string();
        int i = 0;
        int aryan = finalfinal.size();
        while (i < aryan)
        {
            if (finalfinal[i] == '0')
            {
                i++;
                continue;
            }
            else
            {
                break;
            }
        }
        finalfinal = finalfinal.substr(i, finalfinal.size());
        e = new UnlimitedInt(finalfinal);
        e->sign = s;
        return e;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    string finalremainder = "0";
    int s = 1;
    if ((i1->sign == 1 && i2->sign == 1) || (i2->sign == -1 && i1->sign == -1))
    {
        s = 1;
    }
    else
    {
        s = -1;
    }
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *final = new UnlimitedInt("0");
        return final;
    }
    else if (i2->to_string() == "1")
    {
        UnlimitedInt *final = new UnlimitedInt(i1->to_string());
        return final;
    }
    else if (abs_greater_than(i2, i1) && s == 1)
    {
        UnlimitedInt *final = new UnlimitedInt("0");
        return final;
    }
    else if (!abs_greater_than(i2, i1) && !abs_greater_than(i1, i2) && s == 1)
    {
        UnlimitedInt *final = new UnlimitedInt("1");
        return final;
    }
    else if (!abs_greater_than(i2, i1) && !abs_greater_than(i1, i2) && s == -1)
    {
        UnlimitedInt *final = new UnlimitedInt("-1");
        return final;
    }
    else
    {
        UnlimitedInt *a = new UnlimitedInt(i1->to_string());
        UnlimitedInt *b = new UnlimitedInt(i2->to_string());
        a->sign = 1;
        b->sign = 1;
        string a1 = a->to_string();
        string a2 = a1;
        string a3 = a1;
        int maxS = a1.size();
        string finale = "";
        UnlimitedInt *c = new UnlimitedInt("1");
        int i = 0;
        a1 = a2.substr(i, 1);
        while (i < maxS)
        {
            UnlimitedInt *d = new UnlimitedInt("0");
            UnlimitedInt *temp = new UnlimitedInt(a1);
            while (temp->sign == 1)
            {
                d = add(d, c);
                temp = sub(temp, b);
            }
            d = sub(d, c);
            temp = add(temp, b);
            a1 = temp->to_string() + a2.substr(i + 1, 1);
            finale += d->to_string();
            int k = 0;
            while (k < a1.size())
            {
                if (a1[k] == '0')
                {
                    k++;
                    continue;
                }
                else
                {
                    break;
                }
            }
            a1 = a1.substr(k, a1.size());
            finalremainder = temp->to_string();
            delete temp;
            delete d;
            i++;
        }
        int j = 0;
        int madhavan = finale.size();
        while (j < madhavan)
        {
            if (finale[j] == '0')
            {
                j++;
                continue;
            }
            else
            {
                finale = finale.substr(j, finale.size());
                break;
            }
        }
        delete a;
        delete b;
        UnlimitedInt *ovr = new UnlimitedInt(finale);
        if (s == -1 && finalremainder != "0")
        {
            UnlimitedInt *answerf = add(ovr, c);
            delete ovr;
            answerf->sign = s;
            delete c;
            return answerf;
        }
        else
        {
            delete c;
            ovr->sign = s;
            return ovr;
        }
    }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *final = new UnlimitedInt("0");
        return final;
    }
    else if (abs_greater_than(i2, i1))
    {
        UnlimitedInt *final = new UnlimitedInt(i1->to_string());
        return final;
    }
    else if (!abs_greater_than(i2, i1) && !abs_greater_than(i1, i2))
    {
        UnlimitedInt *final = new UnlimitedInt("0");
        return final;
    }
    else
    {
        UnlimitedInt *a = div(i1, i2);
        UnlimitedInt *b = mul(i2, a);
        UnlimitedInt *res = sub(i1, b);
        delete a;
        delete b;
        return res;
    }
}

string UnlimitedInt::to_string()
{
    string result;
    for (int i = 0; i < size; i++)
    {
        result += std::to_string(unlimited_int[i]);
    }

    if (sign == -1)
    {
        result = "-" + result;
    }
    return result;
}

int main()
{
    UnlimitedInt *a = new UnlimitedInt("-9");
    UnlimitedInt *b = new UnlimitedInt("-8");
    // UnlimitedInt *aingo = UnlimitedInt::add(a, b);
    // UnlimitedInt *bingo = UnlimitedInt::sub(a, b);
    UnlimitedInt *cingo = UnlimitedInt::mul(a, b);
    // UnlimitedInt *dingo = UnlimitedInt::div(a, b);
    // UnlimitedInt *eingo = UnlimitedInt::mod(a, b);
    // cout << aingo->to_string() << endl;
    // cout << bingo->to_string() << endl;
    cout << cingo->to_string() << endl;
    // cout << dingo->to_string() << endl;
    // cout << eingo->to_string() << endl;
    // delete bingo;
    // delete aingo;
    // delete cingo;
    // delete dingo;
    // delete eingo;
    return 0;
}