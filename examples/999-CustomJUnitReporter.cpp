#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

namespace Catch {
    class JunitWithTagsReporter: public JunitReporter {
        public:
        JunitWithTagsReporter(ReporterConfig const& _config):
            JunitReporter(_config) {
            }

        ~JunitWithTagsReporter() override = default;

        static std::string joinStrings(const std::string& sep, const std::vector<std::string>& strings) {
            std::ostringstream os;
            if(strings.size() > 0){
                os << strings.front();
                for(auto it=strings.begin()+1;it < strings.end();++it) {
                    os << sep << *it;
                }
            }
            return os.str();
        }
        void writeSectionProperties(SectionNode const& /*sectionNode*/,
                                    TestCaseNode const& testCaseNode) override {
             xml.scopedElement("property")
                 .writeAttribute("name", "tags")
                 .writeAttribute("value", joinStrings(",", testCaseNode.value.testInfo.tags));
        }

        static std::string getDescription() {
            return "Same as junit, but include the test case's tags separated by commas.";
        }
    };

    CATCH_REGISTER_REPORTER("junit_with_tags", JunitWithTagsReporter)
}  // namespace Catch

TEST_CASE("Test", "[Tag1][Tag2][Tag3]") {
    CHECK(1 == 1);
}
