


/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/

#include "main.h"

extern int yydebug;
std::map<std::string, int> myST;
std::map<std::string, int> sizeST;
int LastSTAddress = 5;
bool isCurrConst = false;
bool checkCurr = false;
int curr = 0;
double dcurr = 0;
bool fromBinOp = false;
bool fromFunc = false;
int conCnt = 1;
int lpCnt = 1;
bool iOd = false;
bool fromCase = false;
int currg = 0;
int csnm[] = { 1,1,1,1,1,1,1,1,1,1,1,1 };
int temp = 0;

bool isRecType = false;
bool checkType = false;
int currSize = 0;
bool fromRecList = false;
bool fromVD = false;
int VDSize = 0;

void writeAST(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->print(file);
}
void Pcode(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->pcodegen(file);
}

Object* getTree(char* progFile)
{

	yydebug = 1;
	assert(progFile);

	// yyin is an external variable that been used in yyparse as pointer to the source file.
	yyin = fopen(progFile, "r");
	if (!yyin) {
		cerr << "Error: file " << progFile << " does not exst. Aborting ..." << endl;;
		exit(1);
	}
	assert(yyin);

	// yyparse is yacc function that parse the program, checks syntax and builds the program AST.
	yyparse();

	fclose(yyin);

	// root was initialized in yyparse while it was building the tree.
	// root is the pointer of the returning tree.
	assert(root);
	return(root);
}



int main(int argc, char* argv[])
{
	CodeGenerator codeGen;

	//check input arguments.
	if (argc < 2) {
		cerr << endl << "Input file is missing. Aborting ..." << endl;
		exit(1);
	}

	Object* theProgram = getTree(argv[1]);
	assert(theProgram == root);

	fstream treeFile(TREE_OUTPUT_TEXT_FILE, ios::out);
	fstream pcodeFile(OUTPUT_CODE_TEXT, ios::out);
	treeFile << AST_FILE_HEADER << endl;
	pcodeFile << AST_FILE_HEADER << endl;
	writeAST(theProgram, treeFile);
	Pcode(theProgram, pcodeFile);
	treeFile.close();
	return (0);
}


