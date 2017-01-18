/*
 * TableTest.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: Andrey
 */
#include "tableOfSymbols.h"

class TableTest{
private:
  TableOfSymbols table1;
public:
	/*testplan
	 * add symbols and print them:
	 * few diffrent symbols
	 * same name check that they stack
	 *
	 * */
  bool addition(){
    try
    {
      cout << "add test :" << '\n';
      table1.addSymbol("banana",INT,1);
      table1.addSymbol("apple",INT,2);
      table1.addSymbol("strawbery",REAL,3);
      table1.addSymbol("cherry",REAL,4);
      table1.print();
      return true;
    } catch (string& e)
    {
      cout << "addition test exception :" << '\n' << e << '\n';
      return false;
    } catch (...)
    {
      cout << "addition test unknown exception :" << '\n';
      return false;
    }
  }

  bool masking(){
    if(this->addition())
    {
      try
      {
    	  cout << " addition test success :" << '\n';
    	  cout << "scope masking test :" << '\n';
    	  this->table1.startNewScope();
    	  table1.addSymbol("banana",REAL,2);
    	  table1.addSymbol("apple",REAL,3);
    	  table1.addSymbol("strawbery",INT,4);
          table1.addSymbol("cherry",INT,5);
          table1.print();
          this->table1.endScope();
          table1.print();

      } catch (string& e)
      {
          cout << "scope test exception :"<< '\n' << e << '\n';
          return false;
      } catch (...)
      {
          cout << "scope test unknown exception :" << '\n';
          return false;
      }

      return true;
    }

    cout << " addition test failed :" << '\n';
    return false;
  }// masking

  // error tests: error of variable in the same scope twice
  bool start()
  {
	  if(this->masking())
	  {
	    try
	    {
	    	cout << " masking test success :" << '\n';
	    	cout << " injecttion of scope error test  :" << '\n';
	    	table1.addSymbol("banana",INT,100);
	    	table1.print();
	    } catch (string& e)
	    {
	          cout << "scope error test exception! :"<< '\n' << e << '\n';
	          return true;
	    } catch (...)
	    {
	          cout << "scope error test unknown exception :" << '\n';
	          return false;
	    }
	    cout << "scope error test failure :" << '\n';
	    return false;
	  }

	  cout << " masking test failed :" << '\n';
	  return false;
  } // strat

}; // class

int main(void){
  TableTest test;
  if(test.start())
	  cout << " All tests success!" << '\n';

  return 0;
};

