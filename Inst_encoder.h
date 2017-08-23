#include "pin.H"
extern "C" {
#include "xed-interface.h"
}


int insert_lea(int offset, ADDRINT from_add, ADDRINT dst_add); //load efffective address 
int insert_pushf(); //push flag
int insert_push(ADDRINT source_add); 
int insert_call(ADDRINT dest_add);
int insert_pop(ADDRINT dest_add);
int insert_mov(ADDRINT source_add, ADDRINT dest_add);
int insert_leave(); //clear stack frame