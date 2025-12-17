import PIL.Image as pil_image
import numpy as np
import load_image


def main():
    """
    This program zoom in a picture.
    """
    image: np.array = None
    result: np.array = None

    image = load_image.ft_load("animal.jpeg")
    if (image is None):
        return (None)
    print(image)
    try:
        result = np.array(image[100:500, 400:800])
        result = pil_image.fromarray(result)
        print("New shape after slicing:", np.array(result).shape)
        print(np.array(result))
        result.show()
    except Exception as e:
        print("Error:", e)
        return (None)


if __name__ == "__main__":
    main()
