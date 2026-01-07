def NULL_not_found(object: any) -> int:
	match object:
		case None:
			print("Nothing:", object, type(object))
			return (0)
		case float() if object != object:
			print("Cheese:", object, type(object))
			return (0)
		case "":
			print("Empty:", type(object))
			return (0)
		case 0 if isinstance(object, bool):
			print("Fake:", object, type(object))
			return (0)
		case 0 if isinstance(object, int):
			print("Zero:", object, type(object))
			return (0)
		case _:
			print("Type not Found")
	return (1)
