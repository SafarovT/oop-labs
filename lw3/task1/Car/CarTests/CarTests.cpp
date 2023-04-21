#include "../../../../external/catch2/catch.hpp"
#include "../Car/Car.h"

SCENARIO("Different actions with engine")
{
	GIVEN("Car standing with turned off engine")
	{
		Car car;
		
		WHEN("Changing gear")
		{
			car.SetGear(Gear::First);
		
			THEN("Can not change gear")
			{
				CHECK(car.GetGear() == Gear::Neutral);
			}
		}

		WHEN("Turning on engine")
		{
			car.TurnOnEngine();

			THEN("Can increase speed")
			{
				car.SetGear(Gear::First);
				car.SetSpeed(5);
				CHECK(car.GetSpeed() == 5);

				AND_WHEN("Trying to turn off engine")
				{
					car.TurnOffEngine();

					THEN("Engine is still running")
					{
						CHECK(car.IsTurnedOn());
					}
				}

				AND_WHEN("Trying to turn off engine after stop")
				{
					car.SetSpeed(0);
					car.TurnOffEngine();
					THEN("Can not stop engine")
					{
						CHECK(((car.GetDirection() == Direction::NoDirection) && (car.IsTurnedOn())));
					}

					AND_WHEN("Setting neutral gear")
					{
						car.SetGear(Gear::Neutral);
						car.TurnOffEngine();
						
						THEN("Engine is off")
						{
							CHECK(!car.IsTurnedOn());
						}
					}
				}
			}
		}
	}
}

SCENARIO("Increasing speed on first gear and decreasing speed on neutral gear")
{
	GIVEN("Car standing with turned on engine and first gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::First);

		WHEN("Not enough speed to switch gear")
		{
			car.SetSpeed(19);

			THEN("Can not change gear")
			{
				car.SetGear(Gear::Second);
				CHECK(car.GetGear() == Gear::First);

				AND_WHEN("Gain enough speed to switch gear")
				{
					car.SetSpeed(20);

					THEN("Can change gear")
					{
						car.SetGear(Gear::Second);
						CHECK(car.GetGear() == Gear::Second);

						AND_WHEN("Increasing speed to maximum of gear")
						{
							car.SetSpeed(50);

							THEN("Speed changed")
							{
								CHECK(((car.GetDirection() == Direction::Forward ) && (car.GetSpeed() == 50)));

								AND_WHEN("Trying to increase speed more")
								{
									car.SetSpeed(car.GetSpeed() + 1);

									THEN("Speed did not changed")
									{
										CHECK(car.GetSpeed() == 50);
									}
								}
							}

							AND_WHEN("Switching on neutral gear")
							{
								car.SetGear(Gear::Neutral);

								THEN("Can decrease speed")
								{
									car.SetSpeed(15);
									CHECK(car.GetSpeed() == 15);

									AND_THEN("Can not increase speed")
									{
										car.SetSpeed(20);
										CHECK(car.GetSpeed() == 15);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("Car drives with reverse gear")
{
	GIVEN("Car stands with reverse gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::Reverse);

		WHEN("Increase speed to max")
		{
			car.SetSpeed(20);

			THEN("Car is moving backward with set speed")
			{
				CHECK(((car.GetSpeed() == 20) && (car.GetDirection() == Direction::Backward)));
				
				AND_WHEN("Increasing the speed above max")
				{
					car.SetSpeed(car.GetSpeed() + 1);
					
					THEN("Car speed did not changed")
					{
						CHECK(car.GetSpeed() == 20);
					}
				}
			}

			AND_WHEN("Setting first gear")
			{
				car.SetGear(Gear::First);

				THEN("Failed to set first gear and remains on reverse")
				{
					CHECK(car.GetGear() == Gear::Reverse);

					AND_WHEN("Setting gear to first after stop")
					{
						car.SetSpeed(0);
						car.SetGear(Gear::First);

						THEN("First gear set")
						{
							CHECK(car.GetGear() == Gear::First);
						}
					}
				}
			}
		}

	}
}