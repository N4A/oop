#include "Eval.h"

Eval::Eval()
{

}

Eval::~Eval()
{
    //dtor
}

bool Eval::Func(string strexpress)
{
	unsigned int count = 0;
	for (string::iterator i = strexpress.begin(); i < strexpress.end();i++)
	{
		if ('(' == *i)count++;
	}

	if (0 == count){ return MainUnit(strexpress); }//如果是不含括号的表达式则直接处理。
	else//有括号
	{

		string tmpresult("");
		const string tmp40("0");
		const string tmp41("1");
		string::iterator tmp11 = strexpress.begin();
		string::iterator tmp22 = tmp11 + 1;
		while (('(' != *tmp11) && (tmp11<strexpress.end()))tmp11++;
		tmp22 = tmp11 + 1;
		for (unsigned int jj = 0; jj < count;jj++)
		{
			while (tmp22 < strexpress.end())
			{
				if ('(' == *tmp22){ tmp11 = tmp22; tmp22++; }
				else
				{
					if (')' == *tmp22)
					{
						tmpresult.assign(tmp11 + 1, tmp22);

						if (MainUnit(tmpresult))
						{
							if ((strexpress.begin() == tmp11) && (strexpress.end() - 1 == tmp22)){ return true; }
							if ((strexpress.begin() == tmp11) && (strexpress.end() - 1 > tmp22)){ strexpress.erase(strexpress.begin(), tmp22 + 1); strexpress.insert(strexpress.begin(), tmp41.begin(), tmp41.end()); }
							if ((strexpress.begin() < tmp11) && (strexpress.end() - 1 == tmp22)){ strexpress.erase(tmp11, strexpress.end()); strexpress.append(tmp41); }
							if ((strexpress.begin() < tmp11) && (strexpress.end() - 1 > tmp22)){ strexpress.erase(tmp11, tmp22 + 1); strexpress.insert(tmp11, tmp41.begin(), tmp41.end()); }
						}
						else
						{
							if ((strexpress.begin() == tmp11) && (strexpress.end() - 1 == tmp22)){ return false; }
							if ((strexpress.begin() == tmp11) && (strexpress.end() - 1 > tmp22)){ strexpress.erase(strexpress.begin(), tmp22 + 1); strexpress.insert(strexpress.begin(), tmp40.begin(), tmp40.end()); }
							if ((strexpress.begin() < tmp11) && (strexpress.end() - 1 == tmp22)){ strexpress.erase(tmp11, strexpress.end()); strexpress.append(tmp40); }
							if ((strexpress.begin() < tmp11) && (strexpress.end() - 1 > tmp22)){ strexpress.erase(tmp11, tmp22 + 1); strexpress.insert(tmp11, tmp40.begin(), tmp40.end()); }
						}

						break;
					}
					else
					{
						tmp22++;
					}
				}

			}//while循环

			count = 0;
			for (string::iterator ii = strexpress.begin(); ii < strexpress.end(); ii++)
			{
				if ('(' == *ii)count++;
			}
			if (0 == count){ return MainUnit(strexpress); }//如果是不含括号的表达式则直接处理。
			else
			{
				tmp11 = strexpress.begin();
				tmp22 = tmp11 + 1;
				while (('(' != *tmp11) && (tmp11 < strexpress.end()))tmp11++;

				tmp22 = tmp11 + 1;
			}
		}//大for循环

		//return MainUnit(strexpress);
	}//else反括号
    return false;
}
bool Eval::DelSpace(string strexpress)
{
	if (strexpress.empty())return false;
	else
	{
		string::iterator tmp = strexpress.begin();
		while (' ' == *tmp)
		{
			if (1 == strexpress.size())return false;//&& (1  ==  strexpress.size())
			strexpress.erase(tmp);//删除最开始的空格
		}

		for (string::iterator ii = strexpress.begin()+1; ii < strexpress.end(); ii++)//删除其他空格
		{
			if (' ' == *ii)
			{
				strexpress.erase(ii);
				ii--;
			}
		}
		return true;
	}
}


bool Eval::BasicUnit(string strexpress)//<   >   ==  >=  <=         ||  &&
{
	//这里判断最基本的表达式，3>2   10==10  "adf"=="qwr"
	if (strexpress.empty()){ return false; }
	else
	{

		string::iterator tmp = strexpress.begin();
		while ('0' == *tmp)
		{
			if (1 == strexpress.size())return false;//&& (1  ==  strexpress.size())
			strexpress.erase(tmp);//删除最开始的0
		}
		//if (strexpress.empty()){ return false; }
		unsigned int count = 0;
		string exp1(""),exp2("");
		while ((tmp<strexpress.end()) && ((*tmp) >= 0X30) && ((*tmp) <= 0X39) ){ tmp++; count++; }
		if (count > 0)
		{
			exp1 = strexpress.substr(0, count);
			if (tmp < strexpress.end())
			{
				switch(*tmp)
				{
					case '<':{if ('=' == *(tmp + 1)){ exp2 = strexpress.substr(count + 2, strexpress.size()); if (exp1 <= exp2){ return true; } else{ return false; } } else{ exp2 = strexpress.substr(count + 1, strexpress.size()); if (exp1 < exp2){ return true; } else{ return false; } }}break;
					case '>':{if ('=' == *(tmp + 1)){ exp2 = strexpress.substr(count + 2, strexpress.size()); if (exp1 >= exp2){ return true; } else{ return false; } } else{ exp2 = strexpress.substr(count + 1, strexpress.size()); if (exp1 > exp2){ return true; } else{ return false; } }}break;
					case '=':{ exp2 = strexpress.substr(count + 2, strexpress.size()); if (exp1 == exp2){ return true; } else{ return false; } }break;
				}
			}
			else
			{
				return true;
			}


		}//num compare;
		if ('"' == *tmp)
		{
			tmp++;
			while ('"' != *tmp){ tmp++; count++; }
			if (count > 0)
			{
				exp1 = strexpress.substr(1, count+1);
				tmp++;
				if (tmp < strexpress.end())
				{
					switch (*tmp)
					{
						case '<':{if ('=' == *(tmp + 1)){ exp2 = strexpress.substr(count + 5, strexpress.size() - 1); if (exp1 <= exp2){ return true; } else{ return false; } } else{ exp2 = strexpress.substr(count + 4, strexpress.size() - 1); if (exp1 < exp2){ return true; } else{ return false; } }}break;
						case '>':{if ('=' == *(tmp + 1)){ exp2 = strexpress.substr(count + 5, strexpress.size() - 1); if (exp1 >= exp2){ return true; } else{ return false; } } else{ exp2 = strexpress.substr(count + 4, strexpress.size() - 1); if (exp1 > exp2){ return true; } else{ return false; } }}break;
						case '=':{ exp2 = strexpress.substr(count + 5, strexpress.size() - 1); if (exp1 == exp2){ return true; } else{ return false; } }break;
					}
				}
				else
				{
					return true;
				}
			}
		}//character compare;
	}
    return false;
}

bool Eval::ISlegal(string strexpress)
{
	if (strexpress.empty()){ return false; }


	unsigned int countP = 0, countN = 0;
	for (string::iterator ii = strexpress.begin() ; ii < strexpress.end(); ii++)
	{
		if ('(' == *ii)
		{
			countP++;
		}
		if (')' == *ii)
		{
			countN++;
		}
		if (countN  >  countP)return false;
	}
	if (countN != countP)return false;//保证括号成对


	for (string::iterator ii = strexpress.begin(); ii < strexpress.end()-1; ii++)
	{
		if ('|' == *ii)
		{
			if ('|'  !=  *(++ii)    )
			{
				return false;
			}

		}
		if ('&' == *ii)
		{
			if ('&' != *(++ii))
			{
				return false;
			}
		}

	}//保证||&&整体符号之间没有空格



	if (!DelSpace(strexpress)){ return false; }
	//保证没有空括号、运算符不缺项
	//和一些其他表达错误，有时间可以写全，这里只写一部分
	//假设输入的表达式大体正确，并非故意检测输入健壮性：
	for (string::iterator ii = strexpress.begin(); ii < strexpress.end() - 1; ii++)
	{
		if ('(' == *ii)
		{
			ii++;
			if ('<' == *ii || '>' == *ii || ')' == *ii || '=' == *(++ii) || '|' == *(++ii) || '&' == *(++ii))
			{
				return false;
			}

		}
		if ('>' == *ii || '<' == *ii)
		{
			ii++;
			if (')' == *ii || '>' == *ii || '<' == *ii || '|' == *(++ii) || '&' == *(++ii))
			{
				return false;
			}

		}


	}
	for (string::iterator ii = strexpress.begin(); ii < strexpress.end() ; ii++)
	{
		if (!((((*ii) >= 0X30) && ((*ii) <= 0X39)) || ('(' == *ii) || (')' == *ii) || ('<' == *ii) || ('>' == *ii) || ('=' == *ii) || ('|' == *ii) || ('&' == *ii) || ('"' == *ii) || (((*ii) >= 0X61) && ((*ii) <= 0X7A)) ||( ((*ii) >= 0X41) && ((*ii) <= 0X5A))))return false;
	}
	return true;
}
bool Eval::MainUnit(string strexpress)//这里判断复合表达式，在BasicUnit的基础上  增加||  &&，但是没有括号
{
	if (strexpress.empty()){ return false; }
	else
	{
		unsigned int countORAND =0;
		string result("");
		string tmp("");
        //string tmp11{"0"};
		//string tmp22{"||"};
		//string tmp33{"1"};
		//string tmp44{"&&"};
		string::iterator countmp1 = strexpress.begin();
		string::iterator countmp2 = strexpress.begin();
		for (string::iterator ii = strexpress.begin(); ii < strexpress.end(); ii++)
		{
			if (('|' == *ii) || ('&' == *ii)){ countORAND++; }

		}
		countORAND >>= 1;
		for (unsigned int jj = 0; jj < countORAND;jj++)
		{
			while (('|' != *countmp2) && ('&' != *countmp2) && (countmp2 < strexpress.end())){ countmp2++; }
			if (countmp2 > countmp1)
			{
				tmp.assign(countmp1, countmp2);
				if (BasicUnit(tmp)){ result.append("1"); if (countmp2 < strexpress.end()){ if ('|' == *countmp2) { result.append("||"); } if ('&' == *countmp2) { result.append("&&"); }countmp2 += 2; countmp1 = countmp2; } }
				else{ result.append("0"); if (countmp2 < strexpress.end()){ if ('|' == *countmp2) { result.append("||"); } if ('&' == *countmp2) { result.append("&&"); }countmp2 += 2; countmp1 = countmp2; } }
				//countmp2 += 2;countmp1 = countmp2;

			}
		}
		countmp2 = strexpress.end();
		tmp.assign(countmp1, countmp2);
		if (BasicUnit(tmp)){ result.append("1"); }
		else
		{
			result.append("0");
		}

		return ASSUnit(result);

	}

}
bool Eval::ASSUnit(string strexpress)
{
	string tmp("");
	string tmp11("0");
	string tmp22("1");
	if (tmp11 == strexpress)return false;
	if (tmp22 == strexpress)return true;


	string::iterator head = strexpress.begin();
	string::iterator trail = head + 4;
	while(trail < strexpress.end())
	{
		tmp.assign(head, trail);
		if ("0||0" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp11.begin(), tmp11.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("0||1" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp22.begin(), tmp22.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("0&&0" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp11.begin(), tmp11.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("0&&1" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp11.begin(), tmp11.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("1||0" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp22.begin(), tmp22.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("1||1" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp22.begin(), tmp22.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("1&&0" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp11.begin(), tmp11.end()); head = strexpress.begin(); trail = head + 4; continue; }
		if ("1&&1" == tmp){ strexpress.erase(head, trail); strexpress.insert(head, tmp22.begin(), tmp22.end()); head = strexpress.begin(); trail = head + 4; continue; }

	}
	tmp.assign(head, trail);
	if ("0||0" == tmp){ return false; }
	if ("0||1" == tmp){ return true; }
	if ("0&&0" == tmp){ return false; }
	if ("0&&1" == tmp){ return false; }
	if ("1||0" == tmp){ return true; }
	if ("1||1" == tmp){ return true; }
	if ("1&&0" == tmp){ return false; }
	if ("1&&1" == tmp){ return true; }

	return false;
}
