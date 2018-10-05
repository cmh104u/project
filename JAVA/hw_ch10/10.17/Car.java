//reference : http://urania5872.pixnet.net/blog/post/17434443-%E4%BA%A4%E9%80%9A%E5%B7%A5%E5%85%B7%E6%8E%92%E6%94%BE%E9%87%8F%E6%AF%94%E4%B8%80%E6%AF%94
public class Car implements CarbonFootprint
{
	private double gas;	//Liter
	private final double carbonEmissionPerLiter = 2.36;	//kilogram
	
	public Car(double g)
	{
		gas = g;
	}
	
	@Override
	public double getCarbonFootprint()
	{
		return gas * carbonEmissionPerLiter;
	}
	
	@Override
	public String toString()
	{ 
		return String.format("CAR:\ngas = %.2f L\nCarbon emission per liter = 2.36 kg/L\n", gas);
	}
	
	public double getGas()
	{
		return gas;
	}
	
	public double getCarbonEmissionPerLiter()
	{
		return carbonEmissionPerLiter;
	}
	
	public void setGas(double g)
	{
		gas = g;
	}
	
}
