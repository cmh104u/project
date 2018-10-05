// $ANTLR 3.5.2 myCompiler.g 2018-06-27 20:59:35

    // import packages here.
    import java.util.HashMap;
    import java.util.ArrayList;


import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("all")
public class myCompilerParser extends Parser {
	public static final String[] tokenNames = new String[] {
		"<invalid>", "<EOR>", "<DOWN>", "<UP>", "CHAR", "COMMENT", "EscapeSequence", 
		"FLOAT", "Floating_point_constant", "IF", "INT", "Identifier", "Integer_constant", 
		"STRING_LITERAL", "VOID", "WS", "'('", "')'", "'*'", "'+'", "','", "'-'", 
		"'/'", "';'", "'='", "'{'", "'}'"
	};
	public static final int EOF=-1;
	public static final int T__16=16;
	public static final int T__17=17;
	public static final int T__18=18;
	public static final int T__19=19;
	public static final int T__20=20;
	public static final int T__21=21;
	public static final int T__22=22;
	public static final int T__23=23;
	public static final int T__24=24;
	public static final int T__25=25;
	public static final int T__26=26;
	public static final int CHAR=4;
	public static final int COMMENT=5;
	public static final int EscapeSequence=6;
	public static final int FLOAT=7;
	public static final int Floating_point_constant=8;
	public static final int IF=9;
	public static final int INT=10;
	public static final int Identifier=11;
	public static final int Integer_constant=12;
	public static final int STRING_LITERAL=13;
	public static final int VOID=14;
	public static final int WS=15;

	// delegates
	public Parser[] getDelegates() {
		return new Parser[] {};
	}

	// delegators


	public myCompilerParser(TokenStream input) {
		this(input, new RecognizerSharedState());
	}
	public myCompilerParser(TokenStream input, RecognizerSharedState state) {
		super(input, state);
	}

	@Override public String[] getTokenNames() { return myCompilerParser.tokenNames; }
	@Override public String getGrammarFileName() { return "myCompiler.g"; }


	    boolean TRACEON = false;
	    HashMap<String,Integer> symtab = new HashMap<String,Integer>();
		HashMap<String,Integer> memory = new HashMap<String,Integer>();
	    int labelCount = 0;

		  /*
	    public enum TypeInfo {
	    StringConstant,
	    Integer,
			Float,
			Unknown,
			No_Exist,
			Error
	    }
	    */

	    /* attr_type:
	       1 => integer,
	       2 => float,
	       3 => String constant,
	       -1 => do not exist,
	       -2 => error
	     */
	     
	    List<String> DataCode = new ArrayList<String>();
	    List<String> TextCode = new ArrayList<String>();
	 
	    public static register reg = new register(0, 10);
	    
	    /*
	     * Output prologue.
	     */
	    void prologue(String id)
	    {
	   	   TextCode.add("\n\n/* Text section */");
	       TextCode.add("\t.section .text");
	       TextCode.add("\t.global " + id);
	       TextCode.add("\t.type " + id + ",@function");
	       TextCode.add(id + ":");
	       
	       /* Follow x86 calling convention */
	       TextCode.add("\t pushq %rbp");
	       TextCode.add("\t movq %rsp,%rbp");
	       TextCode.add("\t pushq %rbx"); //callee saved registers.
	       TextCode.add("\t pushq %r12"); //callee saved registers.
	       TextCode.add("\t pushq %r13"); //callee saved registers.
	       TextCode.add("\t pushq %r14"); //callee saved registers.
	       TextCode.add("\t pushq %r15"); //callee saved registers.
	       TextCode.add("\t subq $8,%rsp\n"); // aligned 16-byte boundary.
	    }
	    
	    /*
	     * Output epilogue.
	     */
	    void epilogue()
	    {
	       /* handle epilogue */
	       
	       /* Follow x86 calling convention */
	       TextCode.add("\n\t addq $8,%rsp");
	       TextCode.add("\t popq %r15");
	       TextCode.add("\t popq %r14");
	       TextCode.add("\t popq %r13");
	       TextCode.add("\t popq %r12");
	       TextCode.add("\t popq %rbx");
	       TextCode.add("\t popq %rbp");
		     TextCode.add("\t ret");
	    }
	    
	    
	    /* Generate a new label */
	    String newLabel()
	    {
	       labelCount ++;
	       return (new String("L")) + Integer.toString(labelCount);
	    } 
	    
	    
	    public List<String> getDataCode()
	    {
	       return DataCode;
	    }
	    
	    public List<String> getTextCode()
	    {
	       return TextCode;
	    }



	// $ANTLR start "program"
	// myCompiler.g:104:1: program : declarations functions ;
	public final void program() throws RecognitionException {
		try {
			// myCompiler.g:105:5: ( declarations functions )
			// myCompiler.g:105:7: declarations functions
			{
			pushFollow(FOLLOW_declarations_in_program43);
			declarations();
			state._fsp--;

			pushFollow(FOLLOW_functions_in_program45);
			functions();
			state._fsp--;

			}

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "program"



	// $ANTLR start "functions"
	// myCompiler.g:109:1: functions : ( function functions |);
	public final void functions() throws RecognitionException {
		try {
			// myCompiler.g:110:5: ( function functions |)
			int alt1=2;
			int LA1_0 = input.LA(1);
			if ( (LA1_0==CHAR||LA1_0==FLOAT||LA1_0==INT||LA1_0==VOID) ) {
				alt1=1;
			}
			else if ( (LA1_0==EOF) ) {
				alt1=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 1, 0, input);
				throw nvae;
			}

			switch (alt1) {
				case 1 :
					// myCompiler.g:110:7: function functions
					{
					pushFollow(FOLLOW_function_in_functions63);
					function();
					state._fsp--;

					pushFollow(FOLLOW_functions_in_functions65);
					functions();
					state._fsp--;

					}
					break;
				case 2 :
					// myCompiler.g:112:5: 
					{
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "functions"



	// $ANTLR start "function"
	// myCompiler.g:114:1: function : type Identifier '(' ')' '{' l_declarations statements '}' ;
	public final void function() throws RecognitionException {
		Token Identifier1=null;

		try {
			// myCompiler.g:115:5: ( type Identifier '(' ')' '{' l_declarations statements '}' )
			// myCompiler.g:115:7: type Identifier '(' ')' '{' l_declarations statements '}'
			{
			pushFollow(FOLLOW_type_in_function94);
			type();
			state._fsp--;

			Identifier1=(Token)match(input,Identifier,FOLLOW_Identifier_in_function96); 
			match(input,16,FOLLOW_16_in_function98); 
			match(input,17,FOLLOW_17_in_function100); 
			match(input,25,FOLLOW_25_in_function102); 

			         /* output function prologue */
			         prologue((Identifier1!=null?Identifier1.getText():null));
			      
			pushFollow(FOLLOW_l_declarations_in_function118);
			l_declarations();
			state._fsp--;

			pushFollow(FOLLOW_statements_in_function120);
			statements();
			state._fsp--;

			match(input,26,FOLLOW_26_in_function122); 

				     if (TRACEON)
					     System.out.println("type Identifier () {declarations statements}");
				    
					 /* output function epilogue */	  
				     epilogue();
				  
			}

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "function"



	// $ANTLR start "declarations"
	// myCompiler.g:132:1: declarations : ( type Identifier ';' declarations |);
	public final void declarations() throws RecognitionException {
		Token Identifier2=null;
		int type3 =0;

		try {
			// myCompiler.g:133:5: ( type Identifier ';' declarations |)
			int alt2=2;
			switch ( input.LA(1) ) {
			case INT:
				{
				int LA2_1 = input.LA(2);
				if ( (LA2_1==Identifier) ) {
					int LA2_6 = input.LA(3);
					if ( (LA2_6==23) ) {
						alt2=1;
					}
					else if ( (LA2_6==16) ) {
						alt2=2;
					}

					else {
						int nvaeMark = input.mark();
						try {
							for (int nvaeConsume = 0; nvaeConsume < 3 - 1; nvaeConsume++) {
								input.consume();
							}
							NoViableAltException nvae =
								new NoViableAltException("", 2, 6, input);
							throw nvae;
						} finally {
							input.rewind(nvaeMark);
						}
					}

				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 2, 1, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

				}
				break;
			case FLOAT:
				{
				int LA2_2 = input.LA(2);
				if ( (LA2_2==Identifier) ) {
					int LA2_6 = input.LA(3);
					if ( (LA2_6==23) ) {
						alt2=1;
					}
					else if ( (LA2_6==16) ) {
						alt2=2;
					}

					else {
						int nvaeMark = input.mark();
						try {
							for (int nvaeConsume = 0; nvaeConsume < 3 - 1; nvaeConsume++) {
								input.consume();
							}
							NoViableAltException nvae =
								new NoViableAltException("", 2, 6, input);
							throw nvae;
						} finally {
							input.rewind(nvaeMark);
						}
					}

				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 2, 2, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

				}
				break;
			case VOID:
				{
				int LA2_3 = input.LA(2);
				if ( (LA2_3==Identifier) ) {
					int LA2_6 = input.LA(3);
					if ( (LA2_6==23) ) {
						alt2=1;
					}
					else if ( (LA2_6==16) ) {
						alt2=2;
					}

					else {
						int nvaeMark = input.mark();
						try {
							for (int nvaeConsume = 0; nvaeConsume < 3 - 1; nvaeConsume++) {
								input.consume();
							}
							NoViableAltException nvae =
								new NoViableAltException("", 2, 6, input);
							throw nvae;
						} finally {
							input.rewind(nvaeMark);
						}
					}

				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 2, 3, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

				}
				break;
			case CHAR:
				{
				int LA2_4 = input.LA(2);
				if ( (LA2_4==Identifier) ) {
					int LA2_6 = input.LA(3);
					if ( (LA2_6==23) ) {
						alt2=1;
					}
					else if ( (LA2_6==16) ) {
						alt2=2;
					}

					else {
						int nvaeMark = input.mark();
						try {
							for (int nvaeConsume = 0; nvaeConsume < 3 - 1; nvaeConsume++) {
								input.consume();
							}
							NoViableAltException nvae =
								new NoViableAltException("", 2, 6, input);
							throw nvae;
						} finally {
							input.rewind(nvaeMark);
						}
					}

				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 2, 4, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

				}
				break;
			case EOF:
				{
				alt2=2;
				}
				break;
			default:
				NoViableAltException nvae =
					new NoViableAltException("", 2, 0, input);
				throw nvae;
			}
			switch (alt2) {
				case 1 :
					// myCompiler.g:134:4: type Identifier ';' declarations
					{
					pushFollow(FOLLOW_type_in_declarations150);
					type3=type();
					state._fsp--;

					Identifier2=(Token)match(input,Identifier,FOLLOW_Identifier_in_declarations152); 
					match(input,23,FOLLOW_23_in_declarations154); 
					pushFollow(FOLLOW_declarations_in_declarations156);
					declarations();
					state._fsp--;

					 
						    if (TRACEON) System.out.println("declarations: type Identifier : declarations");
							if (symtab.containsKey((Identifier2!=null?Identifier2.getText():null))) {
							    System.out.println("Type Error: " + 
									                Identifier2.getLine() + 
												    ": Redeclared identifier " + (Identifier2!=null?Identifier2.getText():null));
						    } else {
								/* Add ID and its attr_type into the symbol table. */
								symtab.put((Identifier2!=null?Identifier2.getText():null), type3);
						    }
							
							/* code generation */
							switch(type3) {
							case 1: /* Type: integer, size=> 4 bytes, alignment=> 4 byte boundary. */
							        DataCode.add("\t .common " + (Identifier2!=null?Identifier2.getText():null) + ",4,4\n");
									break;
							case 2: /* Type: float, size=> 4 bytes, alignment=> 4 byte boundary. */
							        DataCode.add("\t .common " + (Identifier2!=null?Identifier2.getText():null) + ",4,4\n");
									break;
							default:
							}
						  
					}
					break;
				case 2 :
					// myCompiler.g:157:7: 
					{
					 if (TRACEON) System.out.println("declarations: ");
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "declarations"



	// $ANTLR start "l_declarations"
	// myCompiler.g:161:1: l_declarations : ( type Identifier ';' l_declarations |);
	public final void l_declarations() throws RecognitionException {
		try {
			// myCompiler.g:162:5: ( type Identifier ';' l_declarations |)
			int alt3=2;
			int LA3_0 = input.LA(1);
			if ( (LA3_0==CHAR||LA3_0==FLOAT||LA3_0==INT||LA3_0==VOID) ) {
				alt3=1;
			}
			else if ( (LA3_0==IF||LA3_0==Identifier||LA3_0==26) ) {
				alt3=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 3, 0, input);
				throw nvae;
			}

			switch (alt3) {
				case 1 :
					// myCompiler.g:163:5: type Identifier ';' l_declarations
					{
					pushFollow(FOLLOW_type_in_l_declarations194);
					type();
					state._fsp--;

					match(input,Identifier,FOLLOW_Identifier_in_l_declarations196); 
					match(input,23,FOLLOW_23_in_l_declarations198); 
					pushFollow(FOLLOW_l_declarations_in_l_declarations200);
					l_declarations();
					state._fsp--;


					      /* If you want to handle local variables, fix it. */ 
					    
					}
					break;
				case 2 :
					// myCompiler.g:168:5: 
					{
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "l_declarations"



	// $ANTLR start "type"
	// myCompiler.g:171:1: type returns [int attr_type] : ( INT | FLOAT | VOID | CHAR );
	public final int type() throws RecognitionException {
		int attr_type = 0;


		try {
			// myCompiler.g:172:5: ( INT | FLOAT | VOID | CHAR )
			int alt4=4;
			switch ( input.LA(1) ) {
			case INT:
				{
				alt4=1;
				}
				break;
			case FLOAT:
				{
				alt4=2;
				}
				break;
			case VOID:
				{
				alt4=3;
				}
				break;
			case CHAR:
				{
				alt4=4;
				}
				break;
			default:
				NoViableAltException nvae =
					new NoViableAltException("", 4, 0, input);
				throw nvae;
			}
			switch (alt4) {
				case 1 :
					// myCompiler.g:172:7: INT
					{
					match(input,INT,FOLLOW_INT_in_type235); 
					 if (TRACEON) System.out.println("type: INT");  attr_type =1; 
					}
					break;
				case 2 :
					// myCompiler.g:173:7: FLOAT
					{
					match(input,FLOAT,FOLLOW_FLOAT_in_type247); 
					 if (TRACEON) System.out.println("type: FLOAT");  attr_type =2; 
					}
					break;
				case 3 :
					// myCompiler.g:174:7: VOID
					{
					match(input,VOID,FOLLOW_VOID_in_type257); 
					}
					break;
				case 4 :
					// myCompiler.g:175:7: CHAR
					{
					match(input,CHAR,FOLLOW_CHAR_in_type265); 
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return attr_type;
	}
	// $ANTLR end "type"



	// $ANTLR start "statements"
	// myCompiler.g:178:1: statements : ( statement statements |);
	public final void statements() throws RecognitionException {
		try {
			// myCompiler.g:178:11: ( statement statements |)
			int alt5=2;
			int LA5_0 = input.LA(1);
			if ( (LA5_0==IF||LA5_0==Identifier) ) {
				alt5=1;
			}
			else if ( (LA5_0==26) ) {
				alt5=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 5, 0, input);
				throw nvae;
			}

			switch (alt5) {
				case 1 :
					// myCompiler.g:178:13: statement statements
					{
					pushFollow(FOLLOW_statement_in_statements277);
					statement();
					state._fsp--;

					pushFollow(FOLLOW_statements_in_statements279);
					statements();
					state._fsp--;

					}
					break;
				case 2 :
					// myCompiler.g:180:5: 
					{
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "statements"



	// $ANTLR start "statement"
	// myCompiler.g:182:1: statement returns [int attr_type] : ( Identifier '=' arith_expression ';' | IF '(' arith_expression ')' if_then_statements | Identifier func_argument );
	public final int statement() throws RecognitionException {
		int attr_type = 0;


		Token Identifier4=null;
		Token Identifier7=null;
		ParserRuleReturnScope arith_expression5 =null;
		String func_argument6 =null;

		try {
			// myCompiler.g:183:5: ( Identifier '=' arith_expression ';' | IF '(' arith_expression ')' if_then_statements | Identifier func_argument )
			int alt6=3;
			int LA6_0 = input.LA(1);
			if ( (LA6_0==Identifier) ) {
				int LA6_1 = input.LA(2);
				if ( (LA6_1==24) ) {
					alt6=1;
				}
				else if ( (LA6_1==16) ) {
					alt6=3;
				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 6, 1, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

			}
			else if ( (LA6_0==IF) ) {
				alt6=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 6, 0, input);
				throw nvae;
			}

			switch (alt6) {
				case 1 :
					// myCompiler.g:183:7: Identifier '=' arith_expression ';'
					{
					Identifier4=(Token)match(input,Identifier,FOLLOW_Identifier_in_statement307); 
					match(input,24,FOLLOW_24_in_statement309); 
					pushFollow(FOLLOW_arith_expression_in_statement311);
					arith_expression5=arith_expression();
					state._fsp--;

					match(input,23,FOLLOW_23_in_statement313); 
					 
						    if (symtab.containsKey((Identifier4!=null?Identifier4.getText():null))) {
						       attr_type = symtab.get((Identifier4!=null?Identifier4.getText():null));
							   memory.put((Identifier4!=null?Identifier4.getText():null), (arith_expression5!=null?((myCompilerParser.arith_expression_return)arith_expression5).value:0));
						    } else {
					         /* Add codes to report and handle this error */
							   System.err.println((Identifier4!=null?Identifier4.getText():null) + " was not declared");
						       attr_type = -2;
						    }
							  
						    if (attr_type != (arith_expression5!=null?((myCompilerParser.arith_expression_return)arith_expression5).attr_type:0)) {
					           System.out.println("Type Error: " + 
							                       (arith_expression5!=null?(arith_expression5.start):null).getLine() +
					 		 	                   ": Type mismatch for the two silde operands in an assignment statement." + attr_type + " : " + (arith_expression5!=null?((myCompilerParser.arith_expression_return)arith_expression5).attr_type:0));
							      attr_type = -2;
					      }
							
							  /* code generation */ 
					      TextCode.add("\t movl " + "$" + (arith_expression5!=null?((myCompilerParser.arith_expression_return)arith_expression5).value:0) + "," + (Identifier4!=null?Identifier4.getText():null) + "(%rip)");
						  
					}
					break;
				case 2 :
					// myCompiler.g:204:7: IF '(' arith_expression ')' if_then_statements
					{
					match(input,IF,FOLLOW_IF_in_statement326); 
					match(input,16,FOLLOW_16_in_statement328); 
					pushFollow(FOLLOW_arith_expression_in_statement330);
					arith_expression();
					state._fsp--;

					match(input,17,FOLLOW_17_in_statement332); 
					pushFollow(FOLLOW_if_then_statements_in_statement334);
					if_then_statements();
					state._fsp--;

					}
					break;
				case 3 :
					// myCompiler.g:205:7: Identifier func_argument
					{
					Identifier7=(Token)match(input,Identifier,FOLLOW_Identifier_in_statement342); 
					pushFollow(FOLLOW_func_argument_in_statement344);
					func_argument6=func_argument();
					state._fsp--;


					      /* code generation */
					      TextCode.add("\t movq " + "$" + func_argument6 + ",%rdi");
					      TextCode.add("\t call " + (Identifier7!=null?Identifier7.getText():null));
					    
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return attr_type;
	}
	// $ANTLR end "statement"



	// $ANTLR start "func_argument"
	// myCompiler.g:214:1: func_argument returns [String label] : ( '(' ')' ';' | '(' a= arith_expression ( ',' b= arith_expression )* ')' ';' );
	public final String func_argument() throws RecognitionException {
		String label = null;


		ParserRuleReturnScope a =null;
		ParserRuleReturnScope b =null;

		try {
			// myCompiler.g:215:5: ( '(' ')' ';' | '(' a= arith_expression ( ',' b= arith_expression )* ')' ';' )
			int alt8=2;
			int LA8_0 = input.LA(1);
			if ( (LA8_0==16) ) {
				int LA8_1 = input.LA(2);
				if ( (LA8_1==17) ) {
					alt8=1;
				}
				else if ( (LA8_1==Floating_point_constant||(LA8_1 >= Identifier && LA8_1 <= STRING_LITERAL)||LA8_1==16||LA8_1==21) ) {
					alt8=2;
				}

				else {
					int nvaeMark = input.mark();
					try {
						input.consume();
						NoViableAltException nvae =
							new NoViableAltException("", 8, 1, input);
						throw nvae;
					} finally {
						input.rewind(nvaeMark);
					}
				}

			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 8, 0, input);
				throw nvae;
			}

			switch (alt8) {
				case 1 :
					// myCompiler.g:215:7: '(' ')' ';'
					{
					match(input,16,FOLLOW_16_in_func_argument372); 
					match(input,17,FOLLOW_17_in_func_argument374); 
					match(input,23,FOLLOW_23_in_func_argument376); 

					        /* handle function calls here. */
					      
					}
					break;
				case 2 :
					// myCompiler.g:219:7: '(' a= arith_expression ( ',' b= arith_expression )* ')' ';'
					{
					match(input,16,FOLLOW_16_in_func_argument392); 
					pushFollow(FOLLOW_arith_expression_in_func_argument398);
					a=arith_expression();
					state._fsp--;


					         /* handle function calls here. */
					         if ((a!=null?((myCompilerParser.arith_expression_return)a).attr_type:0) == 3) { // handle string type.
					            label = newLabel();
					            DataCode.add(label + ":");
					            DataCode.add("\t .string " + (a!=null?((myCompilerParser.arith_expression_return)a).str:null));
					         }
					      
					// myCompiler.g:228:10: ( ',' b= arith_expression )*
					loop7:
					while (true) {
						int alt7=2;
						int LA7_0 = input.LA(1);
						if ( (LA7_0==20) ) {
							alt7=1;
						}

						switch (alt7) {
						case 1 :
							// myCompiler.g:228:12: ',' b= arith_expression
							{
							match(input,20,FOLLOW_20_in_func_argument420); 
							pushFollow(FOLLOW_arith_expression_in_func_argument426);
							b=arith_expression();
							state._fsp--;

							}
							break;

						default :
							break loop7;
						}
					}


									String r = reg.get();
									TextCode.add("\t movl " + "$" + (b!=null?((myCompilerParser.arith_expression_return)b).value:0) + ", %" + r);
									TextCode.add("\t movl " + "%" + r + ",%esi");
								
					match(input,17,FOLLOW_17_in_func_argument441); 
					match(input,23,FOLLOW_23_in_func_argument443); 
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return label;
	}
	// $ANTLR end "func_argument"


	public static class arith_expression_return extends ParserRuleReturnScope {
		public int attr_type;
		public String reg_num;
		public String str;
		public int value;
	};


	// $ANTLR start "arith_expression"
	// myCompiler.g:238:1: arith_expression returns [int attr_type, String reg_num, String str, int value] : a= multExpr ( '+' b= multExpr | '-' c= multExpr )* ;
	public final myCompilerParser.arith_expression_return arith_expression() throws RecognitionException {
		myCompilerParser.arith_expression_return retval = new myCompilerParser.arith_expression_return();
		retval.start = input.LT(1);

		ParserRuleReturnScope a =null;
		ParserRuleReturnScope b =null;
		ParserRuleReturnScope c =null;

		try {
			// myCompiler.g:239:2: (a= multExpr ( '+' b= multExpr | '-' c= multExpr )* )
			// myCompiler.g:239:4: a= multExpr ( '+' b= multExpr | '-' c= multExpr )*
			{
			pushFollow(FOLLOW_multExpr_in_arith_expression468);
			a=multExpr();
			state._fsp--;


				         retval.attr_type = (a!=null?((myCompilerParser.multExpr_return)a).attr_type:0);
				         retval.reg_num = (a!=null?((myCompilerParser.multExpr_return)a).reg_num:null);
				         retval.str = (a!=null?((myCompilerParser.multExpr_return)a).str:null);
						 retval.value = (a!=null?((myCompilerParser.multExpr_return)a).value:0);
				      
			// myCompiler.g:246:5: ( '+' b= multExpr | '-' c= multExpr )*
			loop9:
			while (true) {
				int alt9=3;
				int LA9_0 = input.LA(1);
				if ( (LA9_0==19) ) {
					alt9=1;
				}
				else if ( (LA9_0==21) ) {
					alt9=2;
				}

				switch (alt9) {
				case 1 :
					// myCompiler.g:246:7: '+' b= multExpr
					{
					match(input,19,FOLLOW_19_in_arith_expression485); 
					pushFollow(FOLLOW_multExpr_in_arith_expression491);
					b=multExpr();
					state._fsp--;

					 
								retval.value += (b!=null?((myCompilerParser.multExpr_return)b).value:0);
							  
						        if ((a!=null?((myCompilerParser.multExpr_return)a).attr_type:0) != (b!=null?((myCompilerParser.multExpr_return)b).attr_type:0)) {
								       System.out.println("Type Error: " + 
									                 (a!=null?(a.start):null).getLine() +
											            ": Type mismatch for the operator + in an expression.");
							         retval.attr_type = -2;
							      }
							  
							      /* code generation */
					//          TextCode.add("\t addl " + "%" + (b!=null?((myCompilerParser.multExpr_return)b).reg_num:null) + ", %" + retval.reg_num);
					        
					}
					break;
				case 2 :
					// myCompiler.g:260:6: '-' c= multExpr
					{
					match(input,21,FOLLOW_21_in_arith_expression507); 
					pushFollow(FOLLOW_multExpr_in_arith_expression513);
					c=multExpr();
					state._fsp--;


							retval.value -= (c!=null?((myCompilerParser.multExpr_return)c).value:0);
							if ((a!=null?((myCompilerParser.multExpr_return)a).attr_type:0) != (c!=null?((myCompilerParser.multExpr_return)c).attr_type:0)) {
								System.out.println("Type Error: " + 
									               (a!=null?(a.start):null).getLine() +
											       ": Type mismatch for the operator - in an expression.");
							    retval.attr_type = -2;
							}						  
						  
					}
					break;

				default :
					break loop9;
				}
			}

			}

			retval.stop = input.LT(-1);

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return retval;
	}
	// $ANTLR end "arith_expression"


	public static class multExpr_return extends ParserRuleReturnScope {
		public int attr_type;
		public String reg_num;
		public String str;
		public int value;
	};


	// $ANTLR start "multExpr"
	// myCompiler.g:274:1: multExpr returns [int attr_type, String reg_num, String str, int value] : a= signExpr ( '*' b= signExpr | '/' c= signExpr )* ;
	public final myCompilerParser.multExpr_return multExpr() throws RecognitionException {
		myCompilerParser.multExpr_return retval = new myCompilerParser.multExpr_return();
		retval.start = input.LT(1);

		ParserRuleReturnScope a =null;
		ParserRuleReturnScope b =null;
		ParserRuleReturnScope c =null;

		try {
			// myCompiler.g:275:2: (a= signExpr ( '*' b= signExpr | '/' c= signExpr )* )
			// myCompiler.g:275:4: a= signExpr ( '*' b= signExpr | '/' c= signExpr )*
			{
			pushFollow(FOLLOW_signExpr_in_multExpr545);
			a=signExpr();
			state._fsp--;

			 
				     retval.value = (a!=null?((myCompilerParser.signExpr_return)a).value:0);
					 retval.attr_type = (a!=null?((myCompilerParser.signExpr_return)a).attr_type:0);
				     retval.reg_num = (a!=null?((myCompilerParser.signExpr_return)a).reg_num:null);
				     retval.str = (a!=null?((myCompilerParser.signExpr_return)a).str:null);
				  
			// myCompiler.g:282:7: ( '*' b= signExpr | '/' c= signExpr )*
			loop10:
			while (true) {
				int alt10=3;
				int LA10_0 = input.LA(1);
				if ( (LA10_0==18) ) {
					alt10=1;
				}
				else if ( (LA10_0==22) ) {
					alt10=2;
				}

				switch (alt10) {
				case 1 :
					// myCompiler.g:282:9: '*' b= signExpr
					{
					match(input,18,FOLLOW_18_in_multExpr561); 
					pushFollow(FOLLOW_signExpr_in_multExpr567);
					b=signExpr();
					state._fsp--;


							retval.value *= (b!=null?((myCompilerParser.signExpr_return)b).value:0);
						    if ((a!=null?((myCompilerParser.signExpr_return)a).attr_type:0) != (b!=null?((myCompilerParser.signExpr_return)b).attr_type:0)) {
								System.out.println("Type Error: " + 
									               (a!=null?(a.start):null).getLine() +
											       ": Type mismatch for the operator * in an expression.");
							    retval.attr_type = -2;
							}	
						  
					}
					break;
				case 2 :
					// myCompiler.g:292:9: '/' c= signExpr
					{
					match(input,22,FOLLOW_22_in_multExpr582); 
					pushFollow(FOLLOW_signExpr_in_multExpr588);
					c=signExpr();
					state._fsp--;


							retval.value /= (c!=null?((myCompilerParser.signExpr_return)c).value:0);
							if ((a!=null?((myCompilerParser.signExpr_return)a).attr_type:0) != (c!=null?((myCompilerParser.signExpr_return)c).attr_type:0)) {
								System.out.println("Type Error: " + 
									               (a!=null?(a.start):null).getLine() +
											       ": Type mismatch for the operator / in an expression.");
							    retval.attr_type = -2;
							}	
						  
					}
					break;

				default :
					break loop10;
				}
			}

			}

			retval.stop = input.LT(-1);

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return retval;
	}
	// $ANTLR end "multExpr"


	public static class signExpr_return extends ParserRuleReturnScope {
		public int attr_type;
		public String reg_num;
		public String str;
		public int value;
	};


	// $ANTLR start "signExpr"
	// myCompiler.g:306:1: signExpr returns [int attr_type, String reg_num, String str, int value] : ( primaryExpr | '-' primaryExpr );
	public final myCompilerParser.signExpr_return signExpr() throws RecognitionException {
		myCompilerParser.signExpr_return retval = new myCompilerParser.signExpr_return();
		retval.start = input.LT(1);

		ParserRuleReturnScope primaryExpr8 =null;
		ParserRuleReturnScope primaryExpr9 =null;

		try {
			// myCompiler.g:307:2: ( primaryExpr | '-' primaryExpr )
			int alt11=2;
			int LA11_0 = input.LA(1);
			if ( (LA11_0==Floating_point_constant||(LA11_0 >= Identifier && LA11_0 <= STRING_LITERAL)||LA11_0==16) ) {
				alt11=1;
			}
			else if ( (LA11_0==21) ) {
				alt11=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 11, 0, input);
				throw nvae;
			}

			switch (alt11) {
				case 1 :
					// myCompiler.g:307:4: primaryExpr
					{
					pushFollow(FOLLOW_primaryExpr_in_signExpr615);
					primaryExpr8=primaryExpr();
					state._fsp--;

					 
						     retval.attr_type = (primaryExpr8!=null?((myCompilerParser.primaryExpr_return)primaryExpr8).attr_type:0);
						     retval.reg_num = (primaryExpr8!=null?((myCompilerParser.primaryExpr_return)primaryExpr8).reg_num:null);
						     retval.str = (primaryExpr8!=null?((myCompilerParser.primaryExpr_return)primaryExpr8).str:null);
							 retval.value = (primaryExpr8!=null?((myCompilerParser.primaryExpr_return)primaryExpr8).value:0);
						  
					}
					break;
				case 2 :
					// myCompiler.g:314:4: '-' primaryExpr
					{
					match(input,21,FOLLOW_21_in_signExpr625); 
					pushFollow(FOLLOW_primaryExpr_in_signExpr627);
					primaryExpr9=primaryExpr();
					state._fsp--;

					retval.value = -(primaryExpr9!=null?((myCompilerParser.primaryExpr_return)primaryExpr9).value:0);
					}
					break;

			}
			retval.stop = input.LT(-1);

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return retval;
	}
	// $ANTLR end "signExpr"


	public static class primaryExpr_return extends ParserRuleReturnScope {
		public int attr_type;
		public String reg_num;
		public String str;
		public int value;
	};


	// $ANTLR start "primaryExpr"
	// myCompiler.g:317:1: primaryExpr returns [int attr_type, String reg_num, String str, int value] : ( Integer_constant | Floating_point_constant | STRING_LITERAL | Identifier | '(' arith_expression ')' );
	public final myCompilerParser.primaryExpr_return primaryExpr() throws RecognitionException {
		myCompilerParser.primaryExpr_return retval = new myCompilerParser.primaryExpr_return();
		retval.start = input.LT(1);

		Token Integer_constant10=null;
		Token STRING_LITERAL11=null;
		Token Identifier12=null;
		ParserRuleReturnScope arith_expression13 =null;

		try {
			// myCompiler.g:318:5: ( Integer_constant | Floating_point_constant | STRING_LITERAL | Identifier | '(' arith_expression ')' )
			int alt12=5;
			switch ( input.LA(1) ) {
			case Integer_constant:
				{
				alt12=1;
				}
				break;
			case Floating_point_constant:
				{
				alt12=2;
				}
				break;
			case STRING_LITERAL:
				{
				alt12=3;
				}
				break;
			case Identifier:
				{
				alt12=4;
				}
				break;
			case 16:
				{
				alt12=5;
				}
				break;
			default:
				NoViableAltException nvae =
					new NoViableAltException("", 12, 0, input);
				throw nvae;
			}
			switch (alt12) {
				case 1 :
					// myCompiler.g:318:7: Integer_constant
					{
					Integer_constant10=(Token)match(input,Integer_constant,FOLLOW_Integer_constant_in_primaryExpr646); 
					 
					         retval.attr_type = 1;
					         retval.str = null;
					         retval.value = Integer.parseInt((Integer_constant10!=null?Integer_constant10.getText():null));
							 
					         /* code generation */
					//         retval.reg_num = reg.get();  /* get an register */
					//         TextCode.add("\t movl " + "$" + (Integer_constant10!=null?Integer_constant10.getText():null) + ", %" + retval.reg_num); 
					      
					}
					break;
				case 2 :
					// myCompiler.g:328:7: Floating_point_constant
					{
					match(input,Floating_point_constant,FOLLOW_Floating_point_constant_in_primaryExpr662); 
					 retval.attr_type = 2; 
					}
					break;
				case 3 :
					// myCompiler.g:329:7: STRING_LITERAL
					{
					STRING_LITERAL11=(Token)match(input,STRING_LITERAL,FOLLOW_STRING_LITERAL_in_primaryExpr672); 
					 retval.attr_type = 3; retval.str = (STRING_LITERAL11!=null?STRING_LITERAL11.getText():null); 
					}
					break;
				case 4 :
					// myCompiler.g:330:7: Identifier
					{
					Identifier12=(Token)match(input,Identifier,FOLLOW_Identifier_in_primaryExpr682); 

					         retval.str = null;
					         if(!symtab.containsKey((Identifier12!=null?Identifier12.getText():null))){
								System.err.println("Type Error: "
											        + (Identifier12!=null?Identifier12.getText():null) + " was not declared");
							 }else{
							    retval.attr_type = symtab.get((Identifier12!=null?Identifier12.getText():null));
								retval.value = memory.get((Identifier12!=null?Identifier12.getText():null));
								/* code generation */
								retval.reg_num = reg.get(); /* get an register */
								TextCode.add("\t movl " + (Identifier12!=null?Identifier12.getText():null) + "(%rip), %" + retval.reg_num);
							 }
					      
					}
					break;
				case 5 :
					// myCompiler.g:344:6: '(' arith_expression ')'
					{
					match(input,16,FOLLOW_16_in_primaryExpr697); 
					pushFollow(FOLLOW_arith_expression_in_primaryExpr699);
					arith_expression13=arith_expression();
					state._fsp--;

					match(input,17,FOLLOW_17_in_primaryExpr701); 
					 retval.attr_type = (arith_expression13!=null?((myCompilerParser.arith_expression_return)arith_expression13).attr_type:0); 
													   retval.value = (arith_expression13!=null?((myCompilerParser.arith_expression_return)arith_expression13).value:0);
														
					}
					break;

			}
			retval.stop = input.LT(-1);

		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
		return retval;
	}
	// $ANTLR end "primaryExpr"



	// $ANTLR start "if_then_statements"
	// myCompiler.g:350:1: if_then_statements : ( statement | '{' statements '}' );
	public final void if_then_statements() throws RecognitionException {
		try {
			// myCompiler.g:351:2: ( statement | '{' statements '}' )
			int alt13=2;
			int LA13_0 = input.LA(1);
			if ( (LA13_0==IF||LA13_0==Identifier) ) {
				alt13=1;
			}
			else if ( (LA13_0==25) ) {
				alt13=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 13, 0, input);
				throw nvae;
			}

			switch (alt13) {
				case 1 :
					// myCompiler.g:351:4: statement
					{
					pushFollow(FOLLOW_statement_in_if_then_statements719);
					statement();
					state._fsp--;

					}
					break;
				case 2 :
					// myCompiler.g:352:4: '{' statements '}'
					{
					match(input,25,FOLLOW_25_in_if_then_statements724); 
					pushFollow(FOLLOW_statements_in_if_then_statements726);
					statements();
					state._fsp--;

					match(input,26,FOLLOW_26_in_if_then_statements728); 
					}
					break;

			}
		}
		catch (RecognitionException re) {
			reportError(re);
			recover(input,re);
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "if_then_statements"

	// Delegated rules



	public static final BitSet FOLLOW_declarations_in_program43 = new BitSet(new long[]{0x0000000000004490L});
	public static final BitSet FOLLOW_functions_in_program45 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_function_in_functions63 = new BitSet(new long[]{0x0000000000004490L});
	public static final BitSet FOLLOW_functions_in_functions65 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_type_in_function94 = new BitSet(new long[]{0x0000000000000800L});
	public static final BitSet FOLLOW_Identifier_in_function96 = new BitSet(new long[]{0x0000000000010000L});
	public static final BitSet FOLLOW_16_in_function98 = new BitSet(new long[]{0x0000000000020000L});
	public static final BitSet FOLLOW_17_in_function100 = new BitSet(new long[]{0x0000000002000000L});
	public static final BitSet FOLLOW_25_in_function102 = new BitSet(new long[]{0x0000000004004E90L});
	public static final BitSet FOLLOW_l_declarations_in_function118 = new BitSet(new long[]{0x0000000004000A00L});
	public static final BitSet FOLLOW_statements_in_function120 = new BitSet(new long[]{0x0000000004000000L});
	public static final BitSet FOLLOW_26_in_function122 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_type_in_declarations150 = new BitSet(new long[]{0x0000000000000800L});
	public static final BitSet FOLLOW_Identifier_in_declarations152 = new BitSet(new long[]{0x0000000000800000L});
	public static final BitSet FOLLOW_23_in_declarations154 = new BitSet(new long[]{0x0000000000004490L});
	public static final BitSet FOLLOW_declarations_in_declarations156 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_type_in_l_declarations194 = new BitSet(new long[]{0x0000000000000800L});
	public static final BitSet FOLLOW_Identifier_in_l_declarations196 = new BitSet(new long[]{0x0000000000800000L});
	public static final BitSet FOLLOW_23_in_l_declarations198 = new BitSet(new long[]{0x0000000000004490L});
	public static final BitSet FOLLOW_l_declarations_in_l_declarations200 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_INT_in_type235 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_FLOAT_in_type247 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_VOID_in_type257 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_CHAR_in_type265 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_statement_in_statements277 = new BitSet(new long[]{0x0000000000000A00L});
	public static final BitSet FOLLOW_statements_in_statements279 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_Identifier_in_statement307 = new BitSet(new long[]{0x0000000001000000L});
	public static final BitSet FOLLOW_24_in_statement309 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_arith_expression_in_statement311 = new BitSet(new long[]{0x0000000000800000L});
	public static final BitSet FOLLOW_23_in_statement313 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_IF_in_statement326 = new BitSet(new long[]{0x0000000000010000L});
	public static final BitSet FOLLOW_16_in_statement328 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_arith_expression_in_statement330 = new BitSet(new long[]{0x0000000000020000L});
	public static final BitSet FOLLOW_17_in_statement332 = new BitSet(new long[]{0x0000000002000A00L});
	public static final BitSet FOLLOW_if_then_statements_in_statement334 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_Identifier_in_statement342 = new BitSet(new long[]{0x0000000000010000L});
	public static final BitSet FOLLOW_func_argument_in_statement344 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_16_in_func_argument372 = new BitSet(new long[]{0x0000000000020000L});
	public static final BitSet FOLLOW_17_in_func_argument374 = new BitSet(new long[]{0x0000000000800000L});
	public static final BitSet FOLLOW_23_in_func_argument376 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_16_in_func_argument392 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_arith_expression_in_func_argument398 = new BitSet(new long[]{0x0000000000120000L});
	public static final BitSet FOLLOW_20_in_func_argument420 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_arith_expression_in_func_argument426 = new BitSet(new long[]{0x0000000000120000L});
	public static final BitSet FOLLOW_17_in_func_argument441 = new BitSet(new long[]{0x0000000000800000L});
	public static final BitSet FOLLOW_23_in_func_argument443 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_multExpr_in_arith_expression468 = new BitSet(new long[]{0x0000000000280002L});
	public static final BitSet FOLLOW_19_in_arith_expression485 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_multExpr_in_arith_expression491 = new BitSet(new long[]{0x0000000000280002L});
	public static final BitSet FOLLOW_21_in_arith_expression507 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_multExpr_in_arith_expression513 = new BitSet(new long[]{0x0000000000280002L});
	public static final BitSet FOLLOW_signExpr_in_multExpr545 = new BitSet(new long[]{0x0000000000440002L});
	public static final BitSet FOLLOW_18_in_multExpr561 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_signExpr_in_multExpr567 = new BitSet(new long[]{0x0000000000440002L});
	public static final BitSet FOLLOW_22_in_multExpr582 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_signExpr_in_multExpr588 = new BitSet(new long[]{0x0000000000440002L});
	public static final BitSet FOLLOW_primaryExpr_in_signExpr615 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_21_in_signExpr625 = new BitSet(new long[]{0x0000000000013900L});
	public static final BitSet FOLLOW_primaryExpr_in_signExpr627 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_Integer_constant_in_primaryExpr646 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_Floating_point_constant_in_primaryExpr662 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_STRING_LITERAL_in_primaryExpr672 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_Identifier_in_primaryExpr682 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_16_in_primaryExpr697 = new BitSet(new long[]{0x0000000000213900L});
	public static final BitSet FOLLOW_arith_expression_in_primaryExpr699 = new BitSet(new long[]{0x0000000000020000L});
	public static final BitSet FOLLOW_17_in_primaryExpr701 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_statement_in_if_then_statements719 = new BitSet(new long[]{0x0000000000000002L});
	public static final BitSet FOLLOW_25_in_if_then_statements724 = new BitSet(new long[]{0x0000000004000A00L});
	public static final BitSet FOLLOW_statements_in_if_then_statements726 = new BitSet(new long[]{0x0000000004000000L});
	public static final BitSet FOLLOW_26_in_if_then_statements728 = new BitSet(new long[]{0x0000000000000002L});
}
