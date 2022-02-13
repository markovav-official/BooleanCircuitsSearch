operations = {
    '0001': lambda in1, in2: int(bool(in1) and bool(in2)),
    '0110': lambda in1, in2: int(bool(in1) ^ bool(in2)),
    '0111': lambda in1, in2: int(bool(in1) or bool(in2)),
}


class Circuit:
    def __init__(self):
        self.n_inputs, self.n_steps, self.n_outputs = map(int, input().split())
        self.inputs = input().split()
        self.stage = {}
        self.steps = []
        self.all_results = []
        for _ in range(self.n_steps):
            self.steps.append(input().split())
        self.outputs = input().split()

    def perform_op(self, in1, in2, op):
        if op in operations:
            return operations[op](in1, in2)
        raise NotImplementedError()

    def gen_inputs(self, decimal):
        self.stage = {}
        binary = bin(decimal)[2:]
        binary = (self.n_inputs - len(binary)) * '0' + binary
        for i in range(self.n_inputs):
            self.stage[self.inputs[i]] = (int(binary[i]) if len(binary) > i else 0)

    def perform_steps(self):
        [print(self.stage[inp], end='') for inp in self.inputs]
        print(end=' ')
        result = []
        for step in self.steps:
            self.stage[step[0]] = self.perform_op(self.stage[step[1]], self.stage[step[2]], step[3])
            print(self.stage[step[0]], end=' ')
            result.append(self.stage[step[0]])
        self.all_results.append(result)
        [print(self.stage[out], end='') for out in self.outputs[::-1]]
        print()

    def evaluate(self):
        for i in range(2 ** self.n_inputs):
            self.gen_inputs(i)
            self.perform_steps()


c = Circuit()
c.evaluate()

for column1 in range(len(c.all_results[0])):
    for column2 in range(column1 + 1, len(c.all_results[0])):
        is_equal = True
        for row in range(len(c.all_results)):
            if c.all_results[row][column1] != c.all_results[row][column2]:
                is_equal = False
                break
        if is_equal:
            print(column1, column2)
