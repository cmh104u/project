//reference : https://co2.ftis.org.tw/pagea3_2.asp
public class Building implements CarbonFootprint
{
	private final double lightCarbonEmissionPerHour = 0.8;
	private double lightUsageTime;
	private final double airConditionCarbonEmissionPerHour = 4;
	private double airConditionUsageTime;
	private final double kitchenCarbonEmissionPerHour = 18;
	private double kitchenUsageTime;
	
	public Building(double LT, double AT, double KT)
	{
		lightUsageTime = LT;
		airConditionUsageTime = AT;
		kitchenUsageTime = KT;
	}
	
	@Override
	public double getCarbonFootprint()
	{
		return (lightCarbonEmissionPerHour*lightUsageTime
				+ airConditionCarbonEmissionPerHour*airConditionUsageTime
				+ kitchenCarbonEmissionPerHour*kitchenUsageTime);
	}
	
	@Override
	public String toString()
	{ 
		return String.format("BUILDING:\n%s\n%s\n%s\n%s%.2f\n%s%.2f\n%s%.2f\n", "Light Carbon Emission Per Hour = 0.8 kg/hr"
									   , "Air-Condition Carbon Emission Per Hour = 4 kg/hr"
									   , "Kitchen Carbon Emission Per Hour = 18 kg/hr"
									   , "lightUsageTime = ", lightUsageTime
									   , "airConditionUsageTime = ", airConditionUsageTime
									   , "kitchenUsageTime = ", kitchenUsageTime); 
	}
	
	public double getLightCarbonEmissionPerHour()
	{
		return lightCarbonEmissionPerHour;
	}
	public double getLightUsageTime()
	{
		return lightUsageTime;
	}
	public double getAirConditionCarbonEmissionPerHour()
	{
		return airConditionCarbonEmissionPerHour;
	}
	public double getAirConditionUsageTime()
	{
		return airConditionUsageTime;
	}
	public double getKitchenCarbonEmissionPerHour()
	{
		return kitchenCarbonEmissionPerHour;
	}
	public double getKitchenUsageTime()
	{
		return kitchenUsageTime;
	}
	
	public void setLightUsageTime(double a)
	{
		lightUsageTime = a;
	}
	public void setAirConditionUsageTime(double a)
	{
		airConditionUsageTime = a;
	}
	public void setKitchenUsageTime(double a)
	{
		kitchenUsageTime = a;
	}

	
}
