//
// Created by Maarten Van Loo on 5/10/2022.
//

#include <catch2/catch_all.hpp>
#include <iostream>
#include <Utils/Stopwatch.h>
#include <LinearAlgebra/Vector.h>

#define benchmark false
using namespace MRay;
TEST_CASE("tVector"){
    Vec4 vec1;
    Vec4 vec2;
    Vec4 target1;
    SECTION("Constructors"){
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);

        CHECK(vec1.get(0) == 1); CHECK(vec1.get<0>() == 1);
        CHECK(vec1.get(1) == 2); CHECK(vec1.get<1>() == 2);
        CHECK(vec1.get(2) == 3); CHECK(vec1.get<2>() == 3);
        CHECK(vec1.get(3) == 4); CHECK(vec1.get<3>() == 4);

        Vec3 v = Vec3(5,6,7);
        vec2 = Vec4(v,8);
        CHECK(vec2.get(0) == 5); CHECK(vec2.get<0>() == 5);
        CHECK(vec2.get(1) == 6); CHECK(vec2.get<1>() == 6);
        CHECK(vec2.get(2) == 7); CHECK(vec2.get<2>() == 7);
        CHECK(vec2.get(3) == 8); CHECK(vec2.get<3>() == 8);

        vec1 = vec2; //copy constructor
        CHECK(vec2.get(0) == 5); CHECK(vec2.get<0>() == 5);
        CHECK(vec2.get(1) == 6); CHECK(vec2.get<1>() == 6);
        CHECK(vec2.get(2) == 7); CHECK(vec2.get<2>() == 7);
        CHECK(vec2.get(3) == 8); CHECK(vec2.get<3>() == 8);
    }

    SECTION("Getter & Setters"){
        //templated getter and setters
        vec1.set<0>(9);
        vec1.set<1>(10);
        vec1.set<2>(11);
        vec1.set<3>(12);
        CHECK(vec1.get<0>() == 9);
        CHECK(vec1.get<1>() == 10);
        CHECK(vec1.get<2>() == 11);
        CHECK(vec1.get<3>() == 12);

        //normal getter
        vec2.set<0>(9);
        vec2.set<1>(10);
        vec2.set<2>(11);
        vec2.set<3>(12);
        CHECK(vec2.get(0) == 9);
        CHECK(vec2.get(1) == 10);
        CHECK(vec2.get(2) == 11);
        CHECK(vec2.get(3) == 12);
    }

    SECTION("Vector operations"){
        //dot
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        CHECK((vec1.dot(vec2) - 70) < 5e-6);
        CHECK((Vec4::dot(vec1,vec2) - 70) < 5e-6);

        //cross
        target1 = Vec4(-4,8,-4,0); //TODO:Last value important?
        CHECK((vec1.cross(vec2).get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.cross(vec2).get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.cross(vec2).get<2>() - target1.get<2>()) < 5e-6);
        CHECK((Vec4::cross(vec1,vec2).get<0>() - target1.get<0>()) < 5e-6);
        CHECK((Vec4::cross(vec1,vec2).get<1>() - target1.get<1>()) < 5e-6);
        CHECK((Vec4::cross(vec1,vec2).get<2>() - target1.get<2>()) < 5e-6);

        //cosine of angle
        CHECK((vec1.angle(vec2) - 0.968863931626966) < 5e-6);
        CHECK((Vec4::angle(vec1,vec2) - 0.968863931626966) < 5e-6);
    }

    SECTION("math"){
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        //abs
        CHECK((vec1.abs() - 5.47722557505166) < 5e-6);
        CHECK((Vec4::abs(vec1) - 5.47722557505166) < 5e-6);

        //sum
        CHECK((vec1.sum() - 10) < 5e-6);
        CHECK((Vec4::sum(vec1) - 10) < 5e-6);

        //sum3
        CHECK((vec1.sum3() - 6) < 5e-6);
        CHECK((Vec4::sum3(vec1) - 6) < 5e-6);

        //max
        CHECK((vec1.max() - 4) < 5e-6);
        CHECK((Vec4::max(vec1) - 4) < 5e-6);

        //max3
        CHECK((vec1.max3() - 3) < 5e-6);
        CHECK((Vec4::max3(vec1) - 3) < 5e-6);

        //min
        CHECK((vec1.min() - 1) < 5e-6);
        CHECK((Vec4::min(vec1) - 1) < 5e-6);

        //min3
        CHECK((vec1.min() - 1) < 5e-6);
        CHECK((Vec4::min3(vec1) - 1) < 5e-6);
    }

    SECTION("operators"){
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);

        CHECK_FALSE(vec1 == vec2);
        CHECK(vec1 == vec1);

        CHECK(vec1 != vec2);
        CHECK_FALSE(vec1 != vec1);

        // negate
        target1 = Vec4(-1,-2,-3,-4);
        CHECK((-vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((-vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((-vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((-vec1.get<3>() - target1.get<3>()) < 5e-6);

        // +=
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        target1 = Vec4(6,8,10,12);
        vec1 += vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        vec1 = vec1 + vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        // -=
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,7,9,11);
        target1 = Vec4(-4,-5,-6,-7);
        vec1 -= vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,7,9,11);
        vec1 = vec1 - vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        // *=
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        target1 = Vec4(5,12,21,32);
        vec1 *= vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        target1 = Vec4(4,8,12,16);
        vec1 *= 4;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        target1 = Vec4(5,12,21,32);
        vec1 = vec1 * vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec1 = vec1 * 4;
        target1 = Vec4(4,8,12,16);
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec1 = 4 * vec1;
        target1 = Vec4(4,8,12,16);
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        // /=
        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        target1 = Vec4(1.0/5,2.0/6,3.0/7,4.0/8);
        vec1 /= vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec1 /= 4;
        target1 = Vec4(1.0/4,2.0/4,3.0/4,4.0/4);
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec2 = Vec4(5,6,7,8);
        vec1 = vec1 / vec2;
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec1 = vec1 / 4;
        target1 = Vec4(1.0/4,2.0/4,3.0/4,4.0/4);
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

        vec1 = Vec4(1,2,3,4);
        vec1 = 4.0 / vec1;
        target1 = Vec4(4.0/1.0,4.0/2.0,4.0/3.0,4.0/4.0);
        CHECK((vec1.get<0>() - target1.get<0>()) < 5e-6);
        CHECK((vec1.get<1>() - target1.get<1>()) < 5e-6);
        CHECK((vec1.get<2>() - target1.get<2>()) < 5e-6);
        CHECK((vec1.get<3>() - target1.get<3>()) < 5e-6);

    }
}


#if benchmark
TEST_CASE("tVectorBenchmark"){
    Vec4 vec1;
    Vec4 vec2;
    Stopwatch stopwatch;

    SECTION("Getter & Setters"){
        //templated getter and setters
        BENCHMARK_ADVANCED("Get<int>")(Catch::Benchmark::Chronometer meter) {
                vec1.set<0>(9);
                vec1.set<1>(10);
                vec1.set<2>(11);
                vec1.set<3>(12);
                meter.measure([vec1] { return vec1.get<0>(); });
            };

        //normal getter
        BENCHMARK_ADVANCED("Get(int)")(Catch::Benchmark::Chronometer meter) {
                vec2.set<0>(9);
                vec2.set<1>(10);
                vec2.set<2>(11);
                vec2.set<3>(12);
                meter.measure([vec2] { return vec2.get<0>(); });
            };
    }

    SECTION("Vector operations"){

        //dot
        BENCHMARK_ADVANCED("dot()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1.dot(vec2); });
            };
        BENCHMARK_ADVANCED("Vec4::dot()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return Vec4::dot(vec1,vec2); });
            };

        //cross
        BENCHMARK_ADVANCED("cross()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1.cross(vec2); });
            };
        BENCHMARK_ADVANCED("Vec4::cross()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return Vec4::cross(vec1,vec2); });
            };

        //cosine of angle
        BENCHMARK_ADVANCED("angle()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1.angle(vec2); });
            };
        BENCHMARK_ADVANCED("Vec4::angle()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return Vec4::angle(vec1,vec2); });
            };
    }

    SECTION("math"){
        //abs
        BENCHMARK_ADVANCED("abs()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.abs(); });
            };
        BENCHMARK_ADVANCED("Vec4::abs()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::abs(vec1); });
            };

        //sum
        BENCHMARK_ADVANCED("sum()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.sum(); });
            };
        BENCHMARK_ADVANCED("Vec4::sum()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::sum(vec1); });
            };

        //sum3
        BENCHMARK_ADVANCED("sum3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.sum3(); });
            };
        BENCHMARK_ADVANCED("Vec4::sum3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::sum3(vec1); });
            };


        //max
        BENCHMARK_ADVANCED("max()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.max(); });
            };
        BENCHMARK_ADVANCED("Vec4::max()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::max(vec1); });
            };

        //max3
        BENCHMARK_ADVANCED("max3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.max3(); });
            };
        BENCHMARK_ADVANCED("Vec4::max3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::max3(vec1); });
            };

        //min
        BENCHMARK_ADVANCED("min()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.min(); });
            };
        BENCHMARK_ADVANCED("Vec4::min()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::min(vec1); });
            };

        //min3
        BENCHMARK_ADVANCED("min3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return vec1.min3(); });
            };
        BENCHMARK_ADVANCED("Vec4::min3()")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return Vec4::min3(vec1); });
            };
    }

    SECTION("operators"){
        // negate
        BENCHMARK_ADVANCED("-Vec4")(Catch::Benchmark::Chronometer meter) {
                vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1] { return -vec1; });
            };

        // +=
        BENCHMARK_ADVANCED("Vec4 +  Vec4")(Catch::Benchmark::Chronometer meter) {
                Vec4 vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                Vec4 vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1 + vec2;});
            };

        // -=
        BENCHMARK_ADVANCED("Vec4 -  Vec4")(Catch::Benchmark::Chronometer meter) {
                Vec4 vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                Vec4 vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1 - vec2;});
            };


        // *=
        BENCHMARK_ADVANCED("Vec4 *  Vec4")(Catch::Benchmark::Chronometer meter) {
                Vec4 vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                Vec4 vec2 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                meter.measure([vec1,vec2] { return vec1 * vec2;});
            };
        BENCHMARK_ADVANCED("Vec4 *  float")(Catch::Benchmark::Chronometer meter) {
                Vec4 vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                float vec2 = 4.0;
                meter.measure([vec1,vec2] { return vec1 * vec2;});
            };
        BENCHMARK_ADVANCED("float * Vec4")(Catch::Benchmark::Chronometer meter) {
                Vec4 vec1 = Vec4(rand()%100,rand()%100,rand()%100,rand()%100);
                float vec2 = 4.0;
                meter.measure([vec1,vec2] { return vec2 * vec1;});
            };

        //TODO: finish benchmarks
        // /=
        stopwatch = Stopwatch();
        stopwatch.start();
        for (int i = 0; i < 1e6; i++){
            vec1 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec2 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec1 /= vec2;
        }
        stopwatch.stop();
        std::cout << "Vec4 /= Vec4\t\t" << stopwatch.elapsedms() << "\n";

        stopwatch = Stopwatch();
        stopwatch.start();
        for (int i = 0; i < 1e6; i++){
            vec1 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec1 /= rand()%100+1;
        }
        stopwatch.stop();
        std::cout << "Vec4 /= float\t\t" << stopwatch.elapsedms() << "\n";

        stopwatch = Stopwatch();
        stopwatch.start();
        for (int i = 0; i < 1e6; i++){
            vec1 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec2 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec1  = vec1 / vec2;
        }
        stopwatch.stop();
        std::cout << "Vec4 /  Vec4\t\t" << stopwatch.elapsedms() << "\n";

        stopwatch = Stopwatch();
        stopwatch.start();
        for (int i = 0; i < 1e6; i++){
            vec1 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec2 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec1  = vec1 / (rand()%100+1);
        }
        stopwatch.stop();
        std::cout << "Vec4 /  float\t\t" << stopwatch.elapsedms() << "\n";

                stopwatch = Stopwatch();
        stopwatch.start();
        for (int i = 0; i < 1e6; i++){
            vec1 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec2 = Vec4(rand()%100+1,rand()%100+1,rand()%100+1,rand()%100+1);
            vec1  = (rand()%100+1) / vec1;
        }
        stopwatch.stop();
        std::cout << "float / Vec4\t\t" << stopwatch.elapsedms() << "\n";

    }

}
#endif