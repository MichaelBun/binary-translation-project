#include "Inst_encoder.h"

int insert_lea(int offset, ADDRINT from_add, ADDRINT dst_add){
	//the instraction: lea: offset(reg) dest
	
	
	
	unsigned int olen = 0;
	unsigned int ilen = XED_MAX_INSTRUCTION_BYTES;

	xed_encoder_instruction_t  enc_instr;

	// jmp [rip] (the target address is placed immediately after the instr).
	xed_inst1(&enc_instr, dstate, 
				XED_ICLASS_JMP, 64,
				xed_mem_bd (XED_REG_RIP, xed_disp(0, 32), 64));

	xed_encoder_request_t enc_req;xed_state_t
	xed_encoder_request_zero_set_mode(&enc_req, &dstate);xed_state_t
	xed_bool_t convert_ok = xed_convert_to_encoder_request(&enc_req, &enc_instr);
	if (!convert_ok) {
		cerr << "conversion to encode request failed" << endl;
		return -1;
	}

	char encoded_jump_bytes[MAX_PROBE_JUMP_INSTR_BYTES];
	xed_error_enum_t xed_error = xed_encode(&enc_req, reinterpret_cast<UINT8*>(encoded_jump_bytes), ilen, &olen);
	if (xed_error != XED_ERROR_NONE) {
		cerr << "ENCODE ERROR: " << xed_error_enum_t2str(xed_error) << endl;		
		return -1;;
	}

	if (olen != SIZE_OF_JMP_RIP_INSTR) { 
		cerr << "invalid indirect probe jump" << endl;
		return -1;
	}

	if (KnobVerbose) {
		cerr << "Jump to translated routine: ";
		dump_instr_from_mem ((ADDRINT *)encoded_jump_bytes, from_addr);			
	}

	// Modify the code with the indirect jump probe followed by target addr:
	*(ADDRINT *)(encoded_jump_bytes + olen) = to_addr;

	int rc = safe_code_update(from_addr, (char *)encoded_jump_bytes, 
							  MAX_PROBE_JUMP_INSTR_BYTES, is_code_write_protected);
	if (rc < 0)
		return -1;

	if (KnobVerbose) {
		cerr << "Code After probe: ";
		dump_instr_from_mem ((ADDRINT *)from_addr, from_addr);			
	}		

	return 0;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	unsigned int olen = 0;
	unsigned int ilen = XED_MAX_INSTRUCTION_BYTES;

	xed_encoder_instruction_t  enc_instr;
	
	
	
	
	
}

