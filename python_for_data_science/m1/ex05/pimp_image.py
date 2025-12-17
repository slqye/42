import numpy as np
import PIL.Image as pil_image


def ft_invert(array) -> np.ndarray:
    """
    This function inverts the colors of the image.
    """
    result: np.ndarray = None
    image: pil_image = None

    try:
        if (array is None):
            return (None)
        result = np.full(array.shape, 255, dtype=np.uint8)
        result -= array
        image = pil_image.fromarray(result)
        image.show()
        return (result - array)
    except Exception as e:
        print("Error:", e)
        return (None)


def ft_red(array) -> np.ndarray:
    """
    This function returns the red channel of the image.
    """
    image: pil_image = None

    try:
        if (array is None):
            return (None)
        result = np.zeros(array.shape, dtype=np.uint8)
        result[:, :, 0] = array[:, :, 0]
        image = pil_image.fromarray(result)
        image.show()
        return (result)
    except Exception as e:
        print("Error:", e)
        return (None)


def ft_green(array) -> np.ndarray:
    """
    This function returns the green channel of the image.
    """
    image: pil_image = None

    try:
        if (array is None):
            return (None)
        result = np.zeros(array.shape, dtype=np.uint8)
        result[:, :, 1] = array[:, :, 1]
        image = pil_image.fromarray(result)
        image.show()
        return (result)
    except Exception as e:
        print("Error:", e)
        return (None)


def ft_blue(array) -> np.ndarray:
    """
    This function returns the blue channel of the image.
    """
    image: pil_image = None

    try:
        if (array is None):
            return (None)
        result = np.zeros(array.shape, dtype=np.uint8)
        result[:, :, 2] = array[:, :, 2]
        image = pil_image.fromarray(result)
        image.show()
        return (result)
    except Exception as e:
        print("Error:", e)
        return (None)


def ft_grey(array) -> np.ndarray:
    """
    This function returns the grey channel of the image.
    """
    image: pil_image = None

    try:
        if (array is None):
            return (None)
        result = np.dot(array[:, :, :3], [0.2989, 0.5870, 0.1140])
        result = result.astype(np.uint8)
        image = pil_image.fromarray(result)
        image.show()
        return (result)
    except Exception as e:
        print("Error:", e)
        return (None)
