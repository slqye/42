import PIL.Image as pil_image
import numpy as np


def ft_load(path: str) -> np.ndarray:
    """
    Print image shape and return an array of RGB image's pixels.
    """
    image: pil_image = None
    result: np.ndarray = None

    if not isinstance(path, str):
        print("Error: path must be a string")
        return (None)
    try:
        image = pil_image.open(path)
        result = np.array(image)
        print("The shape of the image is:", result.shape)
    except Exception as e:
        print("Error:", e)
        return (None)
    return (result)
