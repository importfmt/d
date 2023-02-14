import os
import json
import requests

content_type = "application/json; charset=UTF-8"

user_agent = "Mozilla/5.0 (iPhone; CPU iPhone OS 14_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.1 Mobile/15E148 Safari/604.1"

token = "eyJhbGciOiJ3UzUxMiJ9.JyJpc3MiOiJtb2d3ZGluZy11c2VyIiwic3ViIjoie1wibG9naW5UeXBlXCI6XCJpb3NcIixcInVzZXJJZFwiOjEwMjM3ODI5OX0iLCJhdWQiOiJtb2d1ZGluZyIsImV4cCI6MTkzNzc3OTcyNywibmJmIjoxNjIyMTU5NjI3LCJpYXQiOjE2MjIxNjA1Mjd9.bZ2PYKknAKMv_nMp-It3S_4yfb2hrdtpPj1L7c3HExMXu-AF5SUWSJww5OrY0BNI5HYsVrIkzWwLwFO0qj4WQQ"

planId = "964c304f23228e2b13e33de21f8eacfe"

# type = "END"
# type = "START"

def user_login():
	data = {
		"phone": "12345678910",
		"password": "",
		"loginType": "ios"	
	}
	
	data = json.dumps(data)
	url = "https://api.moguding.net:9000/session/user/v1/login"
	headers = {
		"Content-Type": content_type, 
		"User-Agent": user_agent
	}
	
	res = requests.post(url = url, data = data, headers = headers).text
	res = json.loads(res)

	if res["code"] == 200:
		print(res["data"]["token"])
	else:
		print("ERROR: Get user token failed.")
		os._exit(1)

def user_get_planId():
	data = {
		"paramsType": "student"
	}
	data = json.dumps(data)
	url = "https://api.moguding.net:9000/practice/plan/v1/getPlanByStu"
	headers = {
		"Content-Type": content_type, 
		"User-Agent": user_agent,
		"Authorization": token
	}

	res = requests.post(url = url, data = data, headers = headers).text
	res = json.loads(res)
	
	if res["code"] == 200:
		print(res["data"][0]["planId"])
	else:
		print("ERROR: Get user planId failed.")
		os._exit(1)

def user_sign_in():
	data = {
		"country": "中国",
		"address": "江苏省 · 苏州市 · 示范案例",
		"province": "江苏省",
		"state": "NORMAL",
		"city": "苏州市",
		"latitude": "29.581928",
		"longitude":"115.622929",
		"planId": planId,
		"description": "",
		"type": type,
		"device": "ios"
	}
	data = json.dumps(data)
	url = "https://api.moguding.net:9000/attendence/clock/v1/save"
	headers = {
		"Content-Type": content_type, 
		"User-Agent": user_agent,
		"Authorization": token
	}

	res = requests.post(url = url, data = data, headers = headers).text
	res = json.loads(res)

	if res["code"] == 200:
		print(res)
	else:
		print("ERROR: User sign in failed.")
		os._exit(1)
 
if __name__ == "__main__":
	# user_login()
	# user_get_planId()
	# user_sign_in()
