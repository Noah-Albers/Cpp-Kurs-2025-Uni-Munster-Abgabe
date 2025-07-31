#include <gtest/gtest.h>

TEST(MeteorTest, constructorTest){
    Meteor meteor(100,100);

    ASSERT_EQ(meteor.getPosition(),(100,100-));
}