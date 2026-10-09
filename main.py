from tabelGetter import getTable
import json

with open("tableURLsToSkan.txt", "r", encoding="utf-8") as file:
    urlList = [line.strip() for line in file if line.strip()]

for url in urlList:
    print(f"Parsing: {url}")
    try:
        headers, rows = getTable(url)
        dataToSave = {'url': url, 'headers': headers, 'rows': rows}
    except ValueError:
        dataToSave = "На странице не найдено подходящих таблиц"
    

    safeName = url.replace("https://", "").replace("/", "_").replace(":", "")
    with open(f".\\scrapes\\{safeName}.json", "w", encoding="utf-8") as file:
        json.dump(dataToSave, file, ensure_ascii=False, indent=4)
    
