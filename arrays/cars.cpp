#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>

constexpr int TIMER = 2;

class Car{
  public:
    int team = 0;
    double current_speed = 0;
    double distance = 0;
    double current_time = 0;
    double top_speed = 0;
    double acceleration = 0;
    int handling_factor = 0.8;
    bool nitro_available = true;
    bool operator == (const Car &other);
    bool operator < (const Car &other);
    bool operator > (const Car &other);
    void use_nitro();
    void update(const unsigned  new_time);
    void check_surroundings(std::vector<Car> car_teams);
    void print();
    double get_distance();
    Car(const int team_number, const int n_teams);
  private:
    int number_of_teams = 0;

};

Car::Car(int team_number, int n_teams){
  number_of_teams = n_teams;
  team = team_number;
  current_speed=0;
  current_time=0;
  distance = 200 *(number_of_teams - team_number);
  top_speed = 150 + 10 * team_number;
  acceleration = 2 * team_number;
  nitro_available = true;
}

void Car::use_nitro(){
  if(2 * current_speed < top_speed && nitro_available)
    current_speed = 2 * current_speed;
  else
    current_speed = top_speed;

  nitro_available = false;
}

void Car::update(const unsigned  new_time){
  distance += (current_speed * new_time) + (0.5 * acceleration * std::pow(new_time, 2));
  current_speed += acceleration * new_time;
  current_time += new_time;
}

void Car::check_surroundings(std::vector<Car> car_teams){
  for(auto const &car : car_teams)
    if(team != car.team && std::abs(distance - car.distance) <= 10)
      current_speed *= handling_factor;
}

double Car::get_distance(){
  return distance;
}

bool Car::operator == (const Car &other){
  return team == other.team;
}

bool Car::operator < (const Car &other){
  return distance < other.distance;
}

bool Car::operator > (const Car &other){
  return distance > other.distance;
}

void Car::print(){
  std::cout<<"CAR: "<<team<<" DISTANCE: "<<distance<<" SPEED: "<<current_speed<<" TIME: "<<current_time<<std::endl;
}


Car get_min_car(std::vector<Car> cars, std::vector<Car> completed){
  unsigned index = 0;
  std::vector<Car>::iterator it;

  Car min = cars.at(index);

  for(auto &car : cars){
    if(std::find(completed.begin(), completed.end(), min) != completed.end())
      continue;
    else if(car.get_distance() < min.get_distance())
      min = car;

    return car;
  }

}

std::vector<Car> get_cars_ready(int teams){

  std::vector<Car> car_teams = {};

  for(unsigned i=1; i<=teams; ++i){
    Car new_car(i, teams);
    car_teams.push_back(new_car);
  }

  return car_teams;

}

std::vector<Car> race(std::vector<Car> car_teams, int teams, unsigned track_distance){

  std::vector<Car> completed = {};
  unsigned time_elapsed = 0;

  while(true){
    if(completed.size() == teams)
      return car_teams;

    time_elapsed += TIMER;

    for(auto &car : car_teams)
      if(std::find(completed.begin(), completed.end(), car) == completed.end()){
        car.update(time_elapsed);
        car.check_surroundings(car_teams);
      }

    Car last_car = get_min_car(car_teams, completed);
    last_car.use_nitro();

    for(auto &car : car_teams){
      if(std::find(completed.begin(), completed.end(), car) == completed.end()){
        if(car.get_distance() >= track_distance)
          completed.push_back(car);
      }
    }
  }

  return completed;
}

int main(){

  int teams = 4;

  std::vector<Car> car_teams = get_cars_ready(teams);

  std::vector<Car> winners = race(car_teams, teams, 10000);

  for(auto &car : winners)
    car.print();

  return 0;
}
