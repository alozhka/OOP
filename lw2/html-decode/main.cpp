#include <iostream>
#include <unordered_map>
#include <string>

std::string HtmlDecode(std::string const &html) {
    static const std::unordered_map<std::string, char> entityMap = {
        {"&quot;", '"'}, {"&apos;", '\''}, {"&lt;", '<'},
        {"&gt;", '>'}, {"&amp;", '&'}
    };

    std::string result;
    result.reserve(html.size()); // Оптимизация для избежания лишних аллокаций

    size_t i = 0;
    while (i < html.size()) {
        if (html[i] == '&') {
            size_t semicolonPos = html.find(';', i);
            if (semicolonPos != std::string::npos) {
                std::string entity = html.substr(i, semicolonPos - i + 1);
                auto it = entityMap.find(entity);
                if (it != entityMap.end()) {
                    result += it->second;
                    i = semicolonPos + 1;
                    continue;
                }
            }
        }
        result += html[i++];
    }
    return result;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << HtmlDecode(line) << std::endl;
    }
    return 0;
}
