import os
import sys
import cv2
import shutil
import random
import typer
import Augmentation

from tqdm import tqdm


def compute_plant_type_count(directory: str) -> dict:
    """
    Compute number of plant for each disease.
    """
    result: dict = {}
    sub_name: str = None
    plant_type: str = None
    plant_disease: str = None

    for root, _, files in os.walk(directory):
        if root == directory:
            continue
        sub_name = root.split("/")[-1]
        plant_type = sub_name.split("_")[0].lower()
        plant_disease = sub_name.split("_")[-1].lower()
        if plant_type not in result.keys():
            result[plant_type] = {}
        result[plant_type][plant_disease] = (sub_name, len(files))
    return result


def compute_image_augmentations(image: str) -> list:
    """
    Compute all augmentation of the given image.
    """
    image: object = cv2.imread(image)
    collection: list = []

    collection.append(
        Augmentation.compute_rotation(
            image, random.randint(-45, 45)
        )
    )
    collection.append(Augmentation.compute_blur(image, 15))
    collection.append(Augmentation.compute_contrast(image, 1.5))
    collection.append(Augmentation.compute_scale(image, 1.5))
    collection.append(Augmentation.compute_illumination(image, 50))
    collection.append(Augmentation.compute_projective(image, 25))
    return collection


def generate_filler_images(directory: str) -> None:
    """
    Generate filler augmentation images to balance the dataset.
    """
    type_count: list = compute_plant_type_count(directory)
    to_generate: int = 0
    type_max: int = 0
    sub_count: int = 0
    sub_path: str = None

    for plant_type in type_count:
        type_max = max(x[1] for x in type_count[plant_type].values())
        for plant_sub_type in type_count[plant_type]:
            sub_path, sub_count = type_count[plant_type][plant_sub_type]
            to_generate = int((type_max - sub_count) / 6)
            if to_generate == 0:
                continue
            images: list = os.listdir(os.path.join(directory + sub_path))
            for index in tqdm(range(to_generate)):
                image_path: str = os.path.join(
                    directory + sub_path + "/" + images[index]
                )
                new_images = compute_image_augmentations(image_path)
                for idx, image in enumerate(new_images):
                    file_name: str = images[index].removesuffix(".JPG")
                    file_path: str = f"{directory}{sub_path}/{file_name}"
                    cv2.imwrite(
                        f"{file_path}_{Augmentation.AUGMENTATIONS[idx]}.JPG",
                        image
                    )


def generate_dataset(directory: str, outputs: tuple, ratio: float) -> None:
    """
    Split directory's items by a ratio to create training and validation set.
    """
    plant_type: str = None
    path: str = None
    new_path: str = None

    for (root, _, files) in os.walk(directory):
        if len(files) == 0:
            continue
        training = random.sample(files, int(len(files) * ratio))
        validation = set(files) - set(training)
        for index, current_set in enumerate((training, validation)):
            plant_type = root.split("/")[-1]
            os.makedirs(f"{outputs[index]}{plant_type}", exist_ok=True)
            for file in tqdm(current_set):
                path = os.path.join(f"{root}/{file}")
                new_path = os.path.join(f"{outputs[index]}{plant_type}/{file}")
                shutil.copy(path, new_path)


def main(
    directory: str,
    training_output: str = "includes/training/",
    validation_output: str = "includes/validation/",
    ratio: float = 0.8
) -> None:
    """
    Dataset generation CLI entry point.
    """
    print("Generating filler images.")
    generate_filler_images(directory)
    print("Generating training and validation datasets.")
    generate_dataset(directory, (training_output, validation_output), ratio)


if __name__ == "__main__":
    try:
        typer.run(main)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
