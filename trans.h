#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>

using namespace std;

class progCpp {
	protected:
		char **fileSource;
		int linesCount;
	public:
		progCpp();
		virtual ~progCpp         ();
		virtual void open        (char *);
		virtual void save        (char *) const;
		virtual void transInt    (unsigned int);
		virtual void transFloat	 (unsigned int);
		virtual void transBeg    (unsigned int, bool);
		virtual void transEnd	 (unsigned int);
		virtual void transIf     (unsigned int);
		virtual void transWhile  (unsigned int);
		virtual void transAssign (unsigned int);
		virtual bool isCorrCods  (unsigned int) const;
		virtual bool isCorrAsns  (unsigned int) const;
		virtual void translate   ();
};

class progPas : public progCpp {
	private:
		char **fileSource;
		int linesCount;
	public:
		progPas();
		virtual ~progPas         ();
		virtual void open        (char *);
		virtual void save        (char *) const;
		virtual void transInt    (unsigned int, char*);
		virtual void transFloat  (unsigned int, char*);
		virtual void transBeg    (unsigned int, bool*, char*);
		virtual void transEnd    (unsigned int, bool);
		virtual void transIf     (unsigned int);
		virtual void transWhile  (unsigned int);
		virtual void transAssign (unsigned int, bool, char*);
		virtual bool isCorrCods  (unsigned int) const;
		virtual bool isCorrAsns  (unsigned int) const;
		virtual void translate   ();
};

void substring (char *, char *, size_t, size_t);
void putSpaces (char *, unsigned int, unsigned int);
bool isCorrect (char *);
