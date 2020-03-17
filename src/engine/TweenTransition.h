#ifndef TWEENTRANSITION_H
#define TWEENTRANSITION_H

#include <string>

using namespace std;



class TweenTransition {
	

	public:
		TweenTransition(string func);
		double getResult(double x);
		void setFunc(string func);

		string activeFunc = "";

		static string QUAD;
		static string LINEAR;
		
	private:

};



#endif