#pragma once
#include <gtest/gtest.h>
#include "PortalConnection.hpp"

// ======================================================
//                       Checkin
// ======================================================

// Checkin - Good
TEST(Portal_Connection_Test, Checkin_Good) {
    String payload("{\"success\": true, \"hashOfTags\": \"70a649bece58357507fad054a660e470\", \"timestamp\": 1677833210}");
    std::string expectedResult = "70a649bece58357507fad054a660e470";
    auto result = PortalConnection::decodeHashOfAuthedCards(payload);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expectedResult, result.value());
    
}

// Checkin - Success but missing tag hash (should fail test)
TEST(Portal_Connection_Test, Checkin_Good) {
    String payload("{\"success\": true, \"timestamp\": 1677833210}");
    auto result = PortalConnection::decodeHashOfAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}

// Checkin - Failed
TEST(Portal_Connection_Test, Checkin_Failed) {
    String payload("{\"success\": false, \"hashOfTags\": \"70a649bece58357507fad054a660e470\", \"timestamp\": 1677833210}");
    auto result = PortalConnection::decodeHashOfAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}

// Checkin - Garbage
TEST(Portal_Connection_Test, Checkin_Garbage) {
    String payload("{\"succdlfkjfdsa;vm44{}{%1677833210}");
    auto result = PortalConnection::decodeHashOfAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}
TEST(Portal_Connection_Test, Checkin_Malformed_JSON) {
    String payload("{\"success\": true, \"hashOfTags\": \"70a649bece58357507fad054a660e470\", \"timestamp\": 1677833210"); // Missing closing }
    auto result = PortalConnection::decodeHashOfAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}

// ======================================================
//                       Single Card
// ======================================================

// Auth Single Card - Access Granted
TEST(Portal_Connection_Test, Auth_Single_Card_Good) {
    String payload("{\"access\": true, \"session_id\": \"ab8a928a-f030-4350-a948-e2439077dcc4\", \"timestamp\": 1677833150, \"name\": \"Ryan\"}");
    bool expectedResult = true;
    auto result = PortalConnection::decodeCardAuth(payload);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expectedResult, result.value());
}

// Auth Single Card - Failed
TEST(Portal_Connection_Test, Auth_Single_Card_Failed) {
    String payload("{\"access\": false, \"session_id\": \"ab8a928a-f030-4350-a948-e2439077dcc4\", \"timestamp\": 1677833150, \"name\": \"Ryan\"}");
    bool expectedResult = false;
    auto result = PortalConnection::decodeCardAuth(payload);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expectedResult, result.value());
}

// Auth Single Card - JSON missing access object
TEST(Portal_Connection_Test, Auth_Single_Card_Missing_Access_JSON) {
    String payload("{\"session_id\": \"ab8a928a-f030-4350-a948-e2439077dcc4\", \"timestamp\": 1677833150, \"name\": \"Ryan\"}");
    auto result = PortalConnection::decodeCardAuth(payload);
    ASSERT_FALSE(result.has_value());
}

// Auth Single Card - Garbage
TEST(Portal_Connection_Test, Auth_Single_Card_Garbage) {
    String payload("acc85ib32g98v n3n9v983nonv9oin{3[21}$$11]}");
    auto result = PortalConnection::decodeCardAuth(payload);
    ASSERT_FALSE(result.has_value());
}
TEST(Portal_Connection_Test, Auth_Single_Card_Malformed_JSON) {
    String payload("\"{\"access\" false, \"session_id\": \"ab8a928a-f030-4350-a948-e2439077dcc4\", \"timestamp\": 167783315");
    auto result = PortalConnection::decodeCardAuth(payload);
    ASSERT_FALSE(result.has_value());
}

// ======================================================
//                       All Cards
// ======================================================

// All cards - Good
TEST(Portal_Connection_Test, All_Card_Auth_Good) {
    String payload("{\"authorised_tags\": [\"4386766\", \"3552439\"], \"authorised_tags_hash\": \"70a649bece58357507fad054a660e470\"}");
    struct PortalConnection::AuthedCardsResult expectedResult;
    expectedResult.hashOfCards = "70a649bece58357507fad054a660e470";
    expectedResult.cards[0] = 4386766;
    expectedResult.cards[1] = 3552439;

    auto result = PortalConnection::decodeAllAuthedCards(payload);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expectedResult.hashOfCards, result.value().hashOfCards);
    ASSERT_EQ(expectedResult.cards[0], result.value().cards[0]);
    ASSERT_EQ(expectedResult.cards[1], result.value().cards[1]);


}

// All cards - More cards returned than available cache.
// Should not decode.
TEST(Portal_Connection_Test, All_Card_Auth_Too_Many_Cards) {
    // 255 numbers.
    String payload("{\"authorised_tags\": [\"6237555\", \"5964102\", \"5273029\", \"4556408\", \"5657518\", \"5083286\", \"4888731\", \"5492643\", \"5550811\", \"5367182\", \"6954753\", \"5959045\", \"5845137\", \"6764079\", \"5280070\", \"7208095\", \"5764184\", \"4709349\", \"6476093\", \"6728206\", \"5871236\", \"6657847\", \"4678744\", \"6544215\", \"4693869\", \"5196840\", \"5567936\", \"4572732\", \"4923214\", \"5344731\", \"4463113\", \"7061261\", \"5062218\", \"4664045\", \"6881825\", \"4982398\", \"6586628\", \"4635911\", \"5628121\", \"6457256\", \"4861323\", \"6148765\", \"5596686\", \"6346212\", \"5244686\", \"5880989\", \"5156180\", \"7003070\", \"6109310\", \"5611577\", \"6730489\", \"4929046\", \"6008381\", \"4666616\", \"7140716\", \"4934366\", \"6759021\", \"5942093\", \"5831329\", \"4535744\", \"6508228\", \"7106058\", \"7212135\", \"6436076\", \"5394409\", \"4456127\", \"5277136\", \"6084525\", \"6451120\", \"5367764\", \"6974162\", \"7334912\", \"5037217\", \"6317798\", \"5288828\", \"5381834\", \"6665398\", \"5846077\", \"6181513\", \"4806337\", \"6414074\", \"7319916\", \"4569965\", \"6129789\", \"4926011\", \"7293372\", \"5873142\", \"4741981\", \"7061420\", \"6153286\", \"7215057\", \"5168208\", \"5157121\", \"5103689\", \"4979358\", \"7064255\", \"6007436\", \"5328053\", \"5599001\", \"5921665\", \"5375356\", \"7238874\", \"5181182\", \"4704396\", \"5753124\", \"4948931\", \"5899032\", \"5399771\", \"5854074\", \"5158568\", \"5284389\", \"6104401\", \"4513543\", \"6924799\", \"6996928\", \"5758826\", \"5896034\", \"6332541\", \"6669589\", \"5653317\", \"6737669\", \"6592355\", \"6950167\", \"5359841\", \"5566307\", \"4647224\", \"7219806\", \"5751828\", \"4632418\", \"5830948\", \"6501540\", \"7144818\", \"5882966\", \"7343301\", \"6530012\", \"4899690\", \"6538883\", \"5316742\", \"6475562\", \"4458997\", \"7298419\", \"4518101\", \"7386715\", \"6513784\", \"6108345\", \"6254579\", \"6547056\", \"4429022\", \"6275368\", \"5069550\", \"4998422\", \"7072152\", \"6832423\", \"4967721\", \"6954215\", \"6681628\", \"6458899\", \"5505083\", \"5224484\", \"5906486\", \"6869528\", \"4465719\", \"5002617\", \"4780177\", \"4748193\", \"5928428\", \"6092874\", \"4850856\", \"4731510\", \"6461649\", \"5333861\", \"5317703\", \"4583190\", \"6412220\", \"5334262\", \"6351443\", \"6910360\", \"6082519\", \"6761369\", \"6907688\", \"6700340\", \"5469896\", \"4473157\", \"6130890\", \"7113700\", \"6883942\", \"5990101\", \"5887019\", \"5270399\", \"6469786\", \"5164150\", \"4604626\", \"4432267\", \"5149800\", \"7195206\", \"6207020\", \"6671105\", \"6362196\", \"7199077\", \"5255877\", \"5585970\", \"4825848\", \"7024942\", \"5216006\", \"7280270\", \"4908701\", \"6854124\", \"4930982\", \"6302046\", \"6442758\", \"5054125\", \"7330003\", \"4627790\", \"4554240\", \"5155456\", \"7228161\", \"5590507\", \"5383585\", \"4803827\", \"5358324\", \"5658210\", \"4634057\", \"4549191\", \"4474762\", \"6928779\", \"6006779\", \"5029948\", \"5948900\", \"4856554\", \"6375323\", \"5473321\", \"4387617\", \"5401539\", \"5967828\", \"5771828\", \"4388728\", \"5130130\", \"5237686\", \"6535479\", \"6304694\", \"4723998\", \"5761637\", \"6135746\", \"4958628\", \"7302708\", \"5950916\", \"4539129\", \"5099679\", \"7262133\", \"5096581\", \"5523541\", \"7343368\", \"4921512\", \"4386766\", \"3552439\"], \"authorised_tags_hash\": \"70a649bece58357507fad054a660e470\"}");
    auto result = PortalConnection::decodeAllAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}

// All cards - Garbage
TEST(Portal_Connection_Test, All_Card_Auth_Garbage) {
    String payload = (" oifdshgnoij32nv498nvm$#VmmivnV");
    auto result = PortalConnection::decodeAllAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}

// All cards - MalformedJSON
TEST(Portal_Connection_Test, All_Card_Auth_Malformed_JSON) {
    String payload = ("{\"authorised_tags\": [\"7386766\", \"4552439\"], \"authorised_tags_hash\": \"70a649bece58357507fad054a660e470\"}");
    auto result = PortalConnection::decodeAllAuthedCards(payload);
    ASSERT_FALSE(result.has_value());
}
