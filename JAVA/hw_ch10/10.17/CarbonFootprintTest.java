
public class CarbonFootprintTest {

	public static void main(String[] args)
	{
		CarbonFootprint[] carbonFootprintPerDay = new CarbonFootprint[3];
		carbonFootprintPerDay[0] = new Building(10, 6, 2);
		carbonFootprintPerDay[1] = new Car(10);
		carbonFootprintPerDay[2] = new Bicycle(20);
		
		for(CarbonFootprint CF : carbonFootprintPerDay)
		{
			System.out.printf( "%s%s%.2f %s\n\n", CF, "Total carbon footprint : ", CF.getCarbonFootprint(), "kg"); 
		}
	}

}
