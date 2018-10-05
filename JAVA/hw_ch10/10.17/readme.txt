CarbonFootPrint.java是interface，CarbonFootprintTest.java是測試檔
1. Car.java的getCarbonFootprint()是用  汽油公升數(L) * 汽油每公升的碳排放量(KG/L)
2. Building.java的getCarbonFootprint()是分成三部分:(1)電燈	的碳排放量，用使用的時間分別計算在加起來
						(2)空調
						(3)廚房
3. Bicycle.java的getCarbonFootprint()是用 騎腳踏車的距離(MILE) * 每騎一英里需要的能量用吃香蕉來補充需要的香蕉的碳排放量(KG/MILE)