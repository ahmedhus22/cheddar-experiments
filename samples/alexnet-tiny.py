import torch
import torch.nn as nn


class Square(nn.Module):
    def forward(self, x):
        return x * x


class AlexNetTiny(nn.Module):
    def __init__(self):
        super().__init__()

        self.flatten = nn.Flatten()

        self.fc1 = nn.Linear(768, 256)
        self.sq1 = Square()

        self.fc2 = nn.Linear(256, 128)
        self.sq2 = Square()

        self.fc3 = nn.Linear(128, 64)
        self.sq3 = Square()

        self.fc4 = nn.Linear(64, 10)

    def forward(self, x):
        x = self.flatten(x)

        x = self.fc1(x)
        x = self.sq1(x)

        x = self.fc2(x)
        x = self.sq2(x)

        x = self.fc3(x)
        x = self.sq3(x)

        x = self.fc4(x)

        return x


if __name__ == "__main__":
    model = AlexNetTiny()

    x = torch.randn(1, 3, 16, 16)

    y = model(x)

    print(y.shape)      # torch.Size([1, 10])