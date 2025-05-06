
import sqlite3

conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

cursor.execute('CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)')
cursor.executemany('INSERT INTO users (username, password) VALUES (?, ?)', [
    ('admin', 'adminpass'),
    ('user1', 'user1pass'),
    ('user2', 'user2pass')
])

malicious_input = "' OR '1'='1"

print("None Parameterized Queri results:")
unsafe_query = f"SELECT * FROM users WHERE username = '{malicious_input}'"
cursor.execute(unsafe_query)
for row in cursor.fetchall():
    print(row)

print("\n Parameterized Queri results:")
cursor.execute("SELECT * FROM users WHERE username = ?", (malicious_input,))
for row in cursor.fetchall():
    print(row)
