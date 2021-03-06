grammar myCompiler;

options {
    language = Java;
}

@header {
    // import packages here.
    import java.util.HashMap;
    import java.util.ArrayList;
}

@members {
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
       TextCode.add("\t pushq \%rbp");
       TextCode.add("\t movq \%rsp,\%rbp");
       TextCode.add("\t pushq \%rbx"); //callee saved registers.
       TextCode.add("\t pushq \%r12"); //callee saved registers.
       TextCode.add("\t pushq \%r13"); //callee saved registers.
       TextCode.add("\t pushq \%r14"); //callee saved registers.
       TextCode.add("\t pushq \%r15"); //callee saved registers.
       TextCode.add("\t subq $8,\%rsp\n"); // aligned 16-byte boundary.
    }
    
    /*
     * Output epilogue.
     */
    void epilogue()
    {
       /* handle epilogue */
       
       /* Follow x86 calling convention */
       TextCode.add("\n\t addq $8,\%rsp");
       TextCode.add("\t popq \%r15");
       TextCode.add("\t popq \%r14");
       TextCode.add("\t popq \%r13");
       TextCode.add("\t popq \%r12");
       TextCode.add("\t popq \%rbx");
       TextCode.add("\t popq \%rbp");
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
}


program
    : declarations functions
    ;


functions
    : function functions
    |
    ;
				  
function
    : type Identifier '(' ')' '{'
      {
         /* output function prologue */
         prologue($Identifier.text);
      }
      l_declarations statements '}'
      {
	     if (TRACEON)
		     System.out.println("type Identifier () {declarations statements}");
	    
		 /* output function epilogue */	  
	     epilogue();
	  }
	;


/* global declaraction */
declarations
    :
	  type Identifier ';' declarations
      { 
	    if (TRACEON) System.out.println("declarations: type Identifier : declarations");
		if (symtab.containsKey($Identifier.text)) {
		    System.out.println("Type Error: " + 
				                $Identifier.getLine() + 
							    ": Redeclared identifier " + $Identifier.text);
	    } else {
			/* Add ID and its attr_type into the symbol table. */
			symtab.put($Identifier.text, $type.attr_type);
	    }
		
		/* code generation */
		switch($type.attr_type) {
		case 1: /* Type: integer, size=> 4 bytes, alignment=> 4 byte boundary. */
		        DataCode.add("\t .common " + $Identifier.text + ",4,4\n");
				break;
		case 2: /* Type: float, size=> 4 bytes, alignment=> 4 byte boundary. */
		        DataCode.add("\t .common " + $Identifier.text + ",4,4\n");
				break;
		default:
		}
	  }
    | { if (TRACEON) System.out.println("declarations: ");}
    ;


l_declarations
    :
    type Identifier ';' l_declarations
    {
      /* If you want to handle local variables, fix it. */ 
    }
    | 
    ;


type returns [int attr_type]
    : INT   { if (TRACEON) System.out.println("type: INT");  $attr_type=1; }
    | FLOAT { if (TRACEON) System.out.println("type: FLOAT");  $attr_type=2; }
    | VOID
    | CHAR
    ;

statements: statement statements
    |
    ;
	
statement returns [int attr_type]
    : Identifier '=' arith_expression ';'
	  { 
	    if (symtab.containsKey($Identifier.text)) {
	       $attr_type = symtab.get($Identifier.text);
		   memory.put($Identifier.text, $arith_expression.value);
	    } else {
         /* Add codes to report and handle this error */
		   System.err.println($Identifier.text + " was not declared");
	       $attr_type = -2;
	    }
		  
	    if ($attr_type != $arith_expression.attr_type) {
           System.out.println("Type Error: " + 
		                       $arith_expression.start.getLine() +
 		 	                   ": Type mismatch for the two silde operands in an assignment statement." + $attr_type + " : " + $arith_expression.attr_type);
		      $attr_type = -2;
      }
		
		  /* code generation */ 
      TextCode.add("\t movl " + "\$" + $arith_expression.value + "," + $Identifier.text + "(\%rip)");
	  }
    | IF '(' arith_expression ')' if_then_statements
    | Identifier func_argument
    {
      /* code generation */
      TextCode.add("\t movq " + "$" + $func_argument.label + ",\%rdi");
      TextCode.add("\t call " + $Identifier.text);
    }
    ;


func_argument returns [String label]
    : '(' ')' ';'
      {
        /* handle function calls here. */
      }
    | '(' a = arith_expression 
      {
         /* handle function calls here. */
         if ($a.attr_type == 3) { // handle string type.
            label = newLabel();
            DataCode.add(label + ":");
            DataCode.add("\t .string " + $a.str);
         }
      }
	        ( ',' b = arith_expression )*
			{
				String r = reg.get();
				TextCode.add("\t movl " + "\$" + $b.value + ", \%" + r);
				TextCode.add("\t movl " + "\%" + r + ",\%esi");
			}
	    ')' ';' 
    ;

	
arith_expression returns [int attr_type, String reg_num, String str, int value]
	: a = multExpr
	      {
	         $attr_type = $a.attr_type;
	         $reg_num = $a.reg_num;
	         $str = $a.str;
			 $value = $a.value;
	      }
    ( '+' b = multExpr
	      { 
			$value += $b.value;
		  
	        if ($a.attr_type != $b.attr_type) {
			       System.out.println("Type Error: " + 
				                 $a.start.getLine() +
						            ": Type mismatch for the operator + in an expression.");
		         $attr_type = -2;
		      }
		  
		      /* code generation */
//          TextCode.add("\t addl " + "\%" + $b.reg_num + ", \%" + $reg_num);
        }
	  | '-' c = multExpr
	  {
		$value -= $c.value;
		if ($a.attr_type != $c.attr_type) {
			System.out.println("Type Error: " + 
				               $a.start.getLine() +
						       ": Type mismatch for the operator - in an expression.");
		    $attr_type = -2;
		}						  
	  }
	  )*
	;

	
multExpr returns [int attr_type, String reg_num, String str, int value]
	: a = signExpr 
	  { 
	     $value = $a.value;
		 $attr_type = $a.attr_type;
	     $reg_num = $a.reg_num;
	     $str = $a.str;
	  }
      ( '*' b = signExpr
	  {
		$value *= $b.value;
	    if ($a.attr_type != $b.attr_type) {
			System.out.println("Type Error: " + 
				               $a.start.getLine() +
						       ": Type mismatch for the operator * in an expression.");
		    $attr_type = -2;
		}	
	  }
      | '/' c = signExpr
	  {
		$value /= $c.value;
		if ($a.attr_type != $c.attr_type) {
			System.out.println("Type Error: " + 
				               $a.start.getLine() +
						       ": Type mismatch for the operator / in an expression.");
		    $attr_type = -2;
		}	
	  }
	  )*
	;


signExpr returns [int attr_type, String reg_num, String str, int value]
	: primaryExpr
	  { 
	     $attr_type = $primaryExpr.attr_type;
	     $reg_num = $primaryExpr.reg_num;
	     $str = $primaryExpr.str;
		 $value = $primaryExpr.value;
	  }
	| '-' primaryExpr{$value = -$primaryExpr.value;}
	;

primaryExpr returns [int attr_type, String reg_num, String str, int value]
    : Integer_constant
      { 
         $attr_type = 1;
         $str = null;
         $value = Integer.parseInt($Integer_constant.text);
		 
         /* code generation */
//         $reg_num = reg.get();  /* get an register */
//         TextCode.add("\t movl " + "\$" + $Integer_constant.text + ", \%" + $reg_num); 
      }
    | Floating_point_constant { $attr_type = 2; }
    | STRING_LITERAL { $attr_type = 3; $str = $STRING_LITERAL.text; }
    | Identifier
      {
         $str = null;
         if(!symtab.containsKey($Identifier.text)){
			System.err.println("Type Error: "
						        + $Identifier.text + " was not declared");
		 }else{
		    $attr_type = symtab.get($Identifier.text);
			$value = memory.get($Identifier.text);
			/* code generation */
			$reg_num = reg.get(); /* get an register */
			TextCode.add("\t movl " + $Identifier.text + "(\%rip), \%" + $reg_num);
		 }
      }
	  | '(' arith_expression ')' { $attr_type = $arith_expression.attr_type; 
								   $value = $arith_expression.value;
									}
    ;

	
if_then_statements
	: statement
	| '{' statements '}'
	;

	
/* description of the tokens */
FLOAT:'float';
INT:'int';
VOID: 'void';
CHAR: 'char';
IF: 'if';

Identifier:('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*;
Integer_constant:'0'..'9'+;
Floating_point_constant:'0'..'9'+ '.' '0'..'9'+;

STRING_LITERAL
    :  '"' ( EscapeSequence | ~('\\'|'"') )* '"'
    ;

fragment
EscapeSequence
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    ;


WS:( ' ' | '\t' | '\r' | '\n' ) {$channel=HIDDEN;};
COMMENT:'/*' .* '*/' {$channel=HIDDEN;};
