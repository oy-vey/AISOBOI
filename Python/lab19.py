import httplib2
from bs4 import BeautifulSoup, SoupStrainer


def links(html):
    result = []
    for line in BeautifulSoup(html, "html.parser",  parse_only=SoupStrainer('a')):
        if line.has_attr('href') and line['href'].startswith('http'):  # comment 2nd part for all links
            result.append(str(line['href']))
    return result

http = httplib2.Http()
status, response = http.request('https://en.wikipedia.org/wiki/Python_(programming_language)')
print(links(response))
