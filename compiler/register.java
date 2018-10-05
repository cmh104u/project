import java.util.Stack;

public class register {
	private Stack<Integer> registerStack=new Stack<Integer>();
	
	/* Registers rax, rbx, rcx, rdx, rsi, rdi, and
	 * r8~r15 are general registers */
	public register(int low,int high)
	{
		int a;
		
		/* set integer registers (available), r0~r10 */
		for (a=high; a>=low; a--)
			registerStack.push(a);		
	}
	
	public String get()
	{
		switch(registerStack.pop()){
			case 0:
				return "eax";
				
			case 1:
				return "ebx";
			
			case 2:
				return "ecx";
			
			case 3:
				return "edx";
			
			case 4:
				return "r8d";
			
			case 5:
				return "r9d";
			
			default:
				return "over6reg";
		}
	}
	
	public void set(String s)
	{
		registerStack.push(Integer.parseInt(s.substring(1)));
	}
}
