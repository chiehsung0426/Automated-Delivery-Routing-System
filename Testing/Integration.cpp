#include "pch.h"
#include "CppUnitTest.h"
#include "fuctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{

	TEST_CLASS(integrationtest)
	{
	public:

		TEST_METHOD(T001)
		{
	
			Truck truck = { 100, 1.0, {8 - 1 , 'Y' - 'A'} };
			Shipment shipment = { 50.0, 0.5, { 24 - 1 , 'Y' - 'A'} };
			bool isValid = validateShipment(shipment.weight, shipment.volume, shipment.destination);
			bool hasSpace = false;
			if (isValid) {
				hasSpace = enoughSpace(truck, shipment);
			}
			Assert::IsTrue(isValid && hasSpace);
		}

		TEST_METHOD(T002)
		{
			Truck truck = { 1200, 5.0, {3 - 1 , 'E' - 'A' } };
			Shipment shipment = { 50.0, 0.5,  {15 - 1 , 'M' - 'A'} };
			bool isValid = validateShipment(shipment.weight, shipment.volume, shipment.destination);
			bool hasSpace = false;
			if (isValid) {
				hasSpace = enoughSpace(truck, shipment);
			}
			Assert::IsTrue(isValid);
			Assert::IsFalse(hasSpace, L"Shipment is  valid, but the truck does not have enough space.");
		}

		TEST_METHOD(T003)
		{   

			Truck truck = { 850, 49.0, {25, 25} };
			Shipment shipment = { 350.0, 1.0, {1, 1} };

			bool isValid = validateShipment(shipment.weight, shipment.volume, shipment.destination);
			bool hasSpace = false;
			if (isValid) {
				hasSpace = enoughSpace(truck, shipment);
			}
			Assert::IsTrue(isValid && hasSpace, L"Shipment is valid and the truck has enough space.");
		}

	};
}