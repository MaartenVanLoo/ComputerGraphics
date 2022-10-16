target_sources(MRay
        PUBLIC
        Object.cpp
        Plane.cpp
        Box.cpp
        Sphere.cpp
        TaperedCylinder.cpp

        BooleanObject.cpp
        BooleanUnion.cpp
        BooleanIntersection.cpp
        BooleanDifference.cpp

        Intersection.cpp
        BoundingBox.cpp
        )
#[[target_sources(I_ComputerGraphics
        PUBLIC
        Object.cpp
        Plane.cpp
        Box.cpp
        Sphere.cpp
        Intersection.cpp
        TaperedCylinder.cpp
        )]]