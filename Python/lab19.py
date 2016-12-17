import httplib2
from bs4 import BeautifulSoup, SoupStrainer


def links(html):
    result = []
    for line in BeautifulSoup(html, "html.parser",  parse_only=SoupStrainer('a')):
        if line.has_attr('href'):
            result.append(line['href'])
    return result

http = httplib2.Http()
status, response = http.request('http://www.sports.ru')
print(links(response))