#add_library(ResponseParser dummy_response_parser.c)
add_library(ResponseParser responseParser.c)

# Dependecies
# target_link_libraries(ResponseParser DependencyName)
target_link_libraries(ResponseParser MyParserUtils)