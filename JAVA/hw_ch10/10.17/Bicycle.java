//reference : https://tw.sports.yahoo.com/news/%E9%A8%8E%E5%96%AE%E8%BB%8A%E6%95%91%E5%9C%B0%E7%90%83%E7%A2%B3%E8%B6%B3%E8%B7%A1%E4%B8%8D%E6%AE%98%E7%95%99.html
public class Bicycle implements CarbonFootprint
{
	private double mile;
	private final double carbonEmissionPerMileByEatingBanana = 0.065;	//kilogram
	
	public Bicycle(double m)
	{
		mile = m;
	}
	
	@Override
	public double getCarbonFootprint()
	{
		return mile * carbonEmissionPerMileByEatingBanana;
	}
	
	@Override
	public String toString()
	{
		return String.format("BICYCLE:\nmile = %.2f miles\nCarbon emission per mile by eating banana = 0.065 kg/mile\n", mile);
	}
	
	public double getMile()
	{
		return mile;
	}
	
	public void setMile(double m)
	{
		mile = m;
	}
}
