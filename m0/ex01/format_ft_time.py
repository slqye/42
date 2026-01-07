import datetime as dt

time = dt.datetime.now()
unix_time = time.timestamp()
print(f"Seconds since January 1, 1970: {'{:,}'.format(unix_time)} or {'{:.2E}'.format(unix_time)} in scientific notation")
print(time.strftime("%b %d %Y"))
