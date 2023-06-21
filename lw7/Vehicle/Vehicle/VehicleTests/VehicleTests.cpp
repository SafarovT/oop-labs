#include "../../../../external/catch2/catch.hpp"
#include "../Vehicle/AllVehicles.h"

SCENARIO("Создание людей разных типов")
{
	WHEN("Создаем обычного человека")
	{
		CPerson person("Петр Иванович Степаненко");

		THEN("Име человека установилось верно")
		{
			CHECK(person.GetName() == "Петр Иванович Степаненко");
		}
	}

	WHEN("Создаем полицейского человека")
	{
		CPoliceMan person("Петр", "УМВД");

		THEN("Име полицейского и его отделение установились верно")
		{
			CHECK(person.GetName() == "Петр");
			CHECK(person.GetDepartmentName() == "УМВД");
		}
	}

	WHEN("Создаем человека гонщика")
	{
		CRacer person("Иван", 12);

		THEN("Име гонщика и количество его наград установилось верно")
		{
			CHECK(person.GetName() == "Иван");
			CHECK(person.GetAwardsCount() == 12);
		}
	}
}

SCENARIO("Создание машин разных типов")
{
	WHEN("Создаем автобус")
	{
		CBus car(40);

		THEN("Количество мест установилось верно, все они не заняты")
		{
			CHECK(car.GetPlaceCount() == 40);
			CHECK(car.GetPassengerCount() == 0);
			CHECK(car.IsEmpty());
			CHECK(!car.IsFull());
		}
	}

	WHEN("Создали такси")
	{
		CTaxi car(3, MakeOfTheCar::KIA);

		THEN("Верно установилась марка машины")
		{
			CHECK(car.GetMakeOfTheCar() == MakeOfTheCar::KIA);
		}
	}

	WHEN("Создали полицейскую машину")
	{
		CPoliceCar car(2, MakeOfTheCar::FORD);

		THEN("Верно установилась марка машины")
		{
			CHECK(car.GetMakeOfTheCar() == MakeOfTheCar::FORD);
		}
	}

	WHEN("Создали спорткар")
	{
		CRacingCar car(1, MakeOfTheCar::TOYOTA);

		THEN("Верно установилась марка машины")
		{
			CHECK(car.GetMakeOfTheCar() == MakeOfTheCar::TOYOTA);
		}
	}
}

SCENARIO("Сценарий номер 1 из задания")
{
	WHEN("Полицейский Джон Смит из Северо-западного полицейского участка садится в свой служебный пятиместный полицейский автомобиль марки Ford")
	{
		CPoliceMan john("Джон Смит", "Северо-западный полицейский участок");
		CPoliceCar johnsCar(5, MakeOfTheCar::FORD);
		johnsCar.AddPassenger(std::make_shared<CPoliceMan>(john));

		AND_WHEN("К нему в автомобиль садится его знакомый коп Джим Кларк из Юго-восточного полицейского участка")
		{
			CPoliceMan jhim("Джим Кларк", "Юго-восточный полицейский участок");
			johnsCar.AddPassenger(std::make_shared<CPoliceMan>(jhim));

			THEN("Программа может вывести имено полицейских и их полицейских участков")
			{
				CHECK(johnsCar.GetPassenger(0).GetName() == "Джон Смит");
				CHECK(johnsCar.GetPassenger(0).GetDepartmentName() == "Северо-западный полицейский участок");
				CHECK(johnsCar.GetPassenger(1).GetName() == "Джим Кларк");
				CHECK(johnsCar.GetPassenger(1).GetDepartmentName() == "Юго-восточный полицейский участок");
			}

			AND_WHEN("В сердцах полицейский Джим Кларк выходит из упомянутой машины своего теперь уже бывшего друга")
			{
				johnsCar.RemovePassenger(1);


				AND_WHEN("останавливает двухместное такси марки Тойота, которым управляет выходец из Индии Раджа Ганди, везущий гонщика Михаэля Шумахера")
				{
					CPerson gandhi("Раджа Ганди");
					CRacer michael("Михаэль Шумахер", 91);
					CTaxi gandhisCar(2, MakeOfTheCar::TOYOTA);
					gandhisCar.AddPassenger(std::make_shared<CPerson>(gandhi));
					gandhisCar.AddPassenger(std::make_shared<CRacer>(michael));

					AND_WHEN("«Убедив» таксиста при помощи своего табельного оружия покинуть машину, полицейский Джим садится в такси на место водителя")
					{
						gandhisCar.RemovePassenger(0);
						gandhisCar.AddPassenger(std::make_shared<CPoliceMan>(jhim));

						THEN("Когда таксист пытается сесть в машину, у него не получается, так как в ней все места заняты")
						{
							CHECK_THROWS_AS(gandhisCar.AddPassenger(std::make_shared<CPerson>(gandhi)), std::logic_error);
						}
					}
				}
			}
		}
	}
}