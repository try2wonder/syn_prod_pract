import requests
from bs4 import BeautifulSoup
import json
import os


def getTable(url):
    
    url = url.strip()

    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"
    }

    try:
        response = requests.get(url, headers=headers)
        if response.status_code != 200:
            return {"status": f"Ошибка запроса: код {response.status_code}"}
    except Exception as e:
        return {"status": f"Не удалось подключиться к сайту: {e}"}

    soup = BeautifulSoup(response.text, 'html.parser')

    # Находим ВСЕ таблицы на странице
    tables = soup.find_all('table', {'class': 'table'})
    
    if not tables:
        return {"status": "На странице не найдено подходящих таблиц"}

    allTablesData = []

    # Перебираем таблицы и нумеруем их
    for index, table in enumerate(tables, start=1):
        try:
            tableHeaders = []
            tableData = []
            
            all_rows = table.find_all('tr')
            if not all_rows:
                continue

            # Безопасно определяем максимальное количество колонок по строкам с td
            first_data_row = next((r for r in all_rows if r.find_all('td')), None)
            if not first_data_row:
                continue
            maxColumns = len(first_data_row.find_all('td'))

            # 1. Собираем заголовки таблицы (th)
            for row in all_rows[:1]:
                columns = row.find_all('th')
                for i in range(min(maxColumns, len(columns))):
                    tableHeaders.append(columns[i].text.strip())

            # 2. Собираем данные из строк таблицы (td)
            for row in all_rows[1:]:
                columns = row.find_all('td')
                if not columns:
                    continue
                    
                rowData = []
                # Итерируемся по колонкам
                for i in range(min(maxColumns, len(columns))):
                    cell = columns[i]
                    
                    # Проверяем, есть ли ссылка <a> внутри ячейки
                    link = cell.find('a')
                    if link and link.get('href'):
                        link_text = link.text.strip()
                        href = link.get('href')
                        
                        # Собираем абсолютную ссылку, если на сайте она относительная
                        if href.startswith('/'):
                            href = "https://synergyuniversity.ru" + href
                            
                        # Записываем в формате: Название (Ссылка)
                        cell_value = f"{link_text} ({href})"
                    else:
                        # Если ссылки нет, берём обычный текст ячейки
                        cell_value = cell.text.strip()
                        
                    rowData.append(cell_value)
                
                if rowData:
                    tableData.append(rowData) 

            # Добавляем собранную таблицу в общий список страницы
            allTablesData.append({
                "table_number": index,
                "headers": tableHeaders,
                "rows": tableData
            })

        except Exception as e:
            print(f"Ошибка при обработке таблицы {index} на {url}: {e}")
            continue

    return {
        "url": url,
        "tables_count": len(allTablesData),
        "tables": allTablesData
    }


# --- Основной блок выполнения ---
os.makedirs(".\\scrapes", exist_ok=True)

with open("tableURLsToSkan.txt", "r", encoding="utf-8") as file:
    urlList = [line.strip() for line in file if line.strip()]

for url in urlList:
    print(f"Parsing: {url}")
    
    # Получаем структурированный словарь данных по всем таблицам страницы
    dataToSave = getTable(url)
    
    # Генерируем безопасное имя файла
    safeName = url.replace("https://", "").replace("/", "_").replace(":", "")
    
    # Сохраняем в JSON
    with open(f".\\scrapes\\{safeName}.json", "w", encoding="utf-8") as file:
        json.dump(dataToSave, file, ensure_ascii=False, indent=4)

print("Парсинг успешно завершен!")
